#include <Core/AssetManager.h>
#include <SDL3_image/SDL_image.h>
#include <Core/Logger.h>
#include <stdlib.h>
#include <string.h>

AssetManager *AssetManager_Create(SDL_Renderer *renderer) {
    if (!renderer) {
        LOG_ERROR("AssetManager_Create: renderer is NULL");
        return NULL;
    }

    AssetManager *manager = malloc(sizeof(AssetManager));
    if (!manager) {
        LOG_CRITICAL("AssetManager_Create: failed to allocate memory");
        return NULL;
    }

    manager->renderer = renderer;
    manager->capacity = 32;
    manager->textures = malloc(sizeof(Texture *) * manager->capacity);
    if (!manager->textures) {
        LOG_CRITICAL("AssetManager_Create: failed to allocate texture array");
        free(manager);
        return NULL;
    }
    memset(manager->textures, 0, sizeof(Texture *) * manager->capacity);
    manager->count = 0;

    LOG_INFO("AssetManager created (capacity=%d)", manager->capacity);
    return manager;
}

Texture *AssetManager_LoadTexture(AssetManager *manager,
                                  const char *filepath,
                                  const char *id,
                                  float x, float y, float scale) {
    if (!manager || !filepath || !id) {
        LOG_ERROR("AssetManager_LoadTexture: invalid parameters");
        return NULL;
    }

    // Check if already loaded
    Texture *existing = AssetManager_GetTexture(manager, id);
    if (existing) {
        LOG_WARN("AssetManager_LoadTexture: texture '%s' already loaded", id);
        return existing;
    }

    LOG_DEBUG("Loading texture '%s' from: %s", id, filepath);

    // Load texture directly
    SDL_Texture *sdl_texture = IMG_LoadTexture(manager->renderer, filepath);
    if (!sdl_texture) {
        LOG_ERROR("Failed to load texture '%s' from %s: %s", id, filepath, SDL_GetError());
        return NULL;
    }

    LOG_DEBUG("Texture loaded successfully: '%s'", id);

    // Create Texture wrapper
    Texture *texture = Texture_Create(id, sdl_texture, x, y, scale);
    if (!texture) {
        LOG_ERROR("Failed to create Texture wrapper for '%s'", id);
        SDL_DestroyTexture(sdl_texture);
        return NULL;
    }

    // Add to cache
    if (manager->count >= manager->capacity) {
        manager->capacity *= 2;
        Texture **new_textures = realloc(manager->textures, sizeof(Texture *) * manager->capacity);
        if (!new_textures) {
            LOG_CRITICAL("Failed to grow texture cache");
            Texture_Destroy(texture);
            SDL_DestroyTexture(sdl_texture);
            return NULL;
        }
        manager->textures = new_textures;
        LOG_DEBUG("Texture cache grown to capacity: %d", manager->capacity);
    }

    manager->textures[manager->count] = texture;
    manager->count++;

    LOG_INFO("Texture '%s' loaded and cached (total: %d)", id, manager->count);
    return texture;
}

Texture *AssetManager_GetTexture(AssetManager *manager, const char *id) {
    if (!manager || !id) {
        LOG_WARN("AssetManager_GetTexture: invalid parameters");
        return NULL;
    }

    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i] &&
            strcmp(Texture_GetID(manager->textures[i]), id) == 0) {
            return manager->textures[i];
        }
    }

    return NULL;
}

void AssetManager_UnloadTexture(AssetManager *manager, const char *id) {
    if (!manager || !id) return;

    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i] &&
            strcmp(Texture_GetID(manager->textures[i]), id) == 0) {

            LOG_DEBUG("Unloading texture '%s'", id);

            SDL_Texture *sdl_tex = Texture_GetSDLTexture(manager->textures[i]);
            if (sdl_tex) {
                SDL_DestroyTexture(sdl_tex);
            }

            Texture_Destroy(manager->textures[i]);

            for (int j = i; j < manager->count - 1; j++) {
                manager->textures[j] = manager->textures[j + 1];
            }
            manager->count--;

            LOG_DEBUG("Texture '%s' unloaded (remaining: %d)", id, manager->count);
            return;
        }
    }

    LOG_WARN("AssetManager_UnloadTexture: texture '%s' not found", id);
}

void AssetManager_PrintStats(const AssetManager *manager) {
    if (!manager) return;

    LOG_INFO("=== AssetManager Stats ===");
    LOG_INFO("Loaded textures: %d/%d", manager->count, manager->capacity);

    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i]) {
            SDL_FRect rect = Texture_GetRect(manager->textures[i]);
            LOG_INFO("  [%d] '%s' - size=%.0fx%.0f, pos=(%.0f,%.0f), refcount=%d",
                     i,
                     Texture_GetID(manager->textures[i]),
                     rect.w, rect.h,
                     rect.x, rect.y,
                     Texture_GetRefCount(manager->textures[i]));
        }
    }
}

void AssetManager_Destroy(AssetManager *manager) {
    if (!manager) return;

    LOG_INFO("Destroying AssetManager");

    for (int i = 0; i < manager->count; i++) {
        if (manager->textures[i]) {
            SDL_Texture *sdl_tex = Texture_GetSDLTexture(manager->textures[i]);
            if (sdl_tex) {
                SDL_DestroyTexture(sdl_tex);
            }
            Texture_Destroy(manager->textures[i]);
        }
    }

    free(manager->textures);
    free(manager);

    LOG_DEBUG("AssetManager destroyed");
}
