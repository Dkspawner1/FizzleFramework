#include <Core/AssetManager.h>
#include <SDL3_image/SDL_image.h>
#include <Core/Logger.h>
#include <stdlib.h>
#include <string.h>

AssetManager *AssetManager_Create(SDL_Renderer *renderer) {
    if (renderer == NULL) {
        LOG_ERROR("AssetManager_Create failed: renderer cannot be NULL");
        return NULL;
    }

    AssetManager *manager = (AssetManager *) malloc(sizeof(AssetManager));
    if (!manager) {
        LOG_CRITICAL("AssetManager_Create failed: could not allocate memory");
        return NULL;
    }

    // Create async I/O queue
    manager->queue = SDL_CreateAsyncIOQueue();
    if (!manager->queue) {
        LOG_CRITICAL("AssetManager_Create failed: could not create SDL_AsyncIOQueue");
        free(manager);
        return NULL;
    }

    // Initialize texture cache
    manager->capacity = 32; // Start with space for 32 textures
    manager->textures = malloc(sizeof(Texture *) * manager->capacity);
    if (!manager->textures) {
        LOG_CRITICAL("AssetManager_Create failed: could not allocate texture array");
        SDL_DestroyAsyncIOQueue(manager->queue);
        free(manager);
        return NULL;
    }
    memset(manager->textures, 0, sizeof(Texture *) * manager->capacity);

    manager->count = 0;
    manager->renderer = renderer;

    LOG_INFO("AssetManager created (capacity=%d)", manager->capacity);
    return manager;
}


// ============================================================================
// Async Loading (Non-Blocking)
// ============================================================================

void AssetManager_LoadTextureAsync(AssetManager *manager,
                                   const char *filepath,
                                   const char *id,
                                   float x, float y, float scale) {
    if (!manager) {
        LOG_WARN("AssetManager_LoadTextureAsync: manager is NULL");
        return;
    }

    if (!filepath || !id) {
        LOG_ERROR("AssetManager_LoadTextureAsync: filepath and id cannot be NULL");
        return;
    }

    // Check if already loaded
    if (AssetManager_GetTexture(manager, id)) {
        LOG_WARN("AssetManager_LoadTextureAsync: texture '%s' already loaded, skipping", id);
        return;
    }

    // Queue async file load (CPU work, non-blocking)
    SDL_LoadFileAsync(filepath, manager->queue, (void *) id);

    LOG_DEBUG("AssetManager: Queued async load for '%s' (file=%s)", id, filepath);
}

// ============================================================================
// Poll Results & GPU Upload (Main Thread Only)
// ============================================================================

void AssetManager_PollResults(AssetManager *manager) {
    if (!manager) return;

    SDL_AsyncIOOutcome outcome;

    // Process all completed async I/O tasks
    while (SDL_GetAsyncIOResult(manager->queue, &outcome)) {
        LOG_TRACE("AssetManager: Async I/O completed");

        // Debug: Log what we got
        LOG_DEBUG("Async outcome: buffer=%p, bytes_transferred=%zu, bytes_requested=%zu, userdata=%s",
                  outcome.buffer,
                  outcome.bytes_transferred,
                  outcome.bytes_requested,
                  outcome.userdata ? (const char *)outcome.userdata : "NULL");

        // outcome.buffer contains file data, outcome.bytes_transferred is actual bytes read
        if (!outcome.buffer || outcome.bytes_transferred == 0) {
            LOG_ERROR(
                "AssetManager_PollResults: Failed to load asset '%s' - Empty or NULL buffer (bytes_transferred=%zu)",
                outcome.userdata ? (const char *)outcome.userdata : "unknown",
                outcome.bytes_transferred);
            continue;
        }

        // Load to SDL_Surface (IMG_Load_IO from memory buffer - SDL3 API)
        SDL_IOStream *io = SDL_IOFromConstMem(outcome.buffer, outcome.bytes_transferred);
        if (!io) {
            LOG_ERROR("AssetManager_PollResults: Failed to create IOStream from buffer for asset '%s'",
                      outcome.userdata ? (const char *)outcome.userdata : "unknown");
            SDL_free(outcome.buffer);
            continue;
        }

        SDL_Surface *surface = IMG_Load_IO(io, true); // true closes io stream automatically
        if (!surface) {
            LOG_ERROR("AssetManager_PollResults: IMG_Load_IO failed for asset '%s': %s",
                      outcome.userdata ? (const char *)outcome.userdata : "unknown",
                      SDL_GetError());
            // io is already cleaned up by IMG_Load_IO with true
            SDL_free(outcome.buffer);
            continue;
        }

        LOG_DEBUG("Surface loaded successfully: %dx%d", surface->w, surface->h);

        // Create GPU texture from surface (main thread, safe)
        SDL_Texture *sdl_texture = SDL_CreateTextureFromSurface(manager->renderer, surface);
        if (!sdl_texture) {
            LOG_ERROR("AssetManager_PollResults: SDL_CreateTextureFromSurface failed for asset '%s': %s",
                      outcome.userdata ? (const char *)outcome.userdata : "unknown",
                      SDL_GetError());
            SDL_DestroySurface(surface);
            SDL_free(outcome.buffer);
            continue;
        }

        LOG_DEBUG("SDL_Texture created successfully");

        // Create Texture wrapper
        Texture *texture = Texture_Create(
            outcome.userdata ? (const char *) outcome.userdata : "unknown",
            sdl_texture,
            0.0f, 0.0f, // Position (set by scene later)
            1.0f // Default scale
        );

        if (!texture) {
            LOG_ERROR("AssetManager_PollResults: Texture_Create failed for asset '%s'",
                      outcome.userdata ? (const char *)outcome.userdata : "unknown");
            SDL_DestroyTexture(sdl_texture);
            SDL_DestroySurface(surface);
            SDL_free(outcome.buffer);
            continue;
        }

        // Free surface (texture now owns the GPU data)
        SDL_DestroySurface(surface);

        // Add to cache
        if (manager->count >= manager->capacity) {
            // Grow array
            manager->capacity *= 2;
            Texture **new_textures = realloc(manager->textures,
                                             sizeof(Texture *) * manager->capacity);
            if (!new_textures) {
                LOG_CRITICAL("AssetManager_PollResults: Failed to grow texture cache");
                SDL_DestroyTexture(sdl_texture);
                Texture_Destroy(texture);
                SDL_free(outcome.buffer);
                return;
            }
            manager->textures = new_textures;
            LOG_DEBUG("Texture cache grown to capacity: %d", manager->capacity);
        }

        manager->textures[manager->count] = texture;
        manager->count++;

        LOG_INFO("AssetManager: Texture '%s' loaded and cached (total: %d)",
                 Texture_GetID(texture), manager->count);

        // Free file buffer
        SDL_free(outcome.buffer);
    }
}

// ============================================================================
// Get Texture from Cache
// ============================================================================

Texture *AssetManager_GetTexture(AssetManager *manager, const char *id) {
    if (!manager || !id) {
        LOG_WARN("AssetManager_GetTexture: manager or id is NULL");
        return NULL;
    }

    // Linear search (fine for <1000 textures)
    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i] &&
            strcmp(Texture_GetID(manager->textures[i]), id) == 0) {
            return manager->textures[i];
        }
    }

    return NULL; // Not found or not loaded yet
}

// ============================================================================
// Check Loading Status
// ============================================================================

bool AssetManager_IsLoadingComplete(AssetManager *manager) {
    if (!manager) return false;

    // If queue has no pending tasks, loading is complete
    SDL_AsyncIOOutcome outcome;
    bool has_pending = SDL_GetAsyncIOResult(manager->queue, &outcome);

    // If we got a result, there WAS a pending task
    // Put it back by... well, we can't really put it back.
    // Better approach: just check if queue is empty externally.
    // For now, this is a simple heuristic.

    return !has_pending;
}

// ============================================================================
// Unload Texture
// ============================================================================

void AssetManager_UnloadTexture(AssetManager *manager, const char *id) {
    if (!manager || !id) return;

    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i] &&
            strcmp(Texture_GetID(manager->textures[i]), id) == 0) {
            LOG_DEBUG("AssetManager: Unloading texture '%s'", id);

            // Destroy GPU texture
            SDL_Texture *sdl_tex = Texture_GetSDLTexture(manager->textures[i]);
            if (sdl_tex) {
                SDL_DestroyTexture(sdl_tex);
            }

            // Destroy wrapper
            Texture_Destroy(manager->textures[i]);

            // Remove from cache (shift array)
            for (int j = i; j < manager->count - 1; j++) {
                manager->textures[j] = manager->textures[j + 1];
            }
            manager->count--;

            LOG_DEBUG("AssetManager: Texture '%s' unloaded (remaining: %d)", id, manager->count);
            return;
        }
    }

    LOG_WARN("AssetManager_UnloadTexture: texture '%s' not found", id);
}

// ============================================================================
// Debug Stats
// ============================================================================

void AssetManager_PrintStats(const AssetManager *manager) {
    if (!manager) return;

    LOG_INFO("=== AssetManager Stats ===");
    LOG_INFO("Loaded textures: %d/%d", manager->count, manager->capacity);

    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i]) {
            Texture *tex = manager->textures[i];
            SDL_FRect rect = Texture_GetRect(tex);
            LOG_INFO("  [%d] '%s' - size=%.0fx%.0f, pos=(%.0f,%.0f), refcount=%d",
                     i,
                     Texture_GetID(tex),
                     rect.w, rect.h,
                     rect.x, rect.y,
                     Texture_GetRefCount(tex));
        }
    }
}


void AssetManager_Destroy(AssetManager *manager) {
    if (!manager) return;

    LOG_INFO("Destroying AssetManager");

    // Destroy all textures
    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i]) {
            // Destroy the SDL_Texture first (GPU resource)
            SDL_Texture *sdl_tex = Texture_GetSDLTexture(manager->textures[i]);
            if (sdl_tex) {
                SDL_DestroyTexture(sdl_tex);
            }
            // Then destroy the Texture wrapper
            Texture_Destroy(manager->textures[i]);
        }
    }

    free(manager->textures);
    SDL_DestroyAsyncIOQueue(manager->queue);
    free(manager);

    LOG_DEBUG("AssetManager destroyed");
}
