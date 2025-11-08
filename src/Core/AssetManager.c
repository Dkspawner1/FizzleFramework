#include <Core/AssetManager.h>
#include <SDL3_image/SDL_image.h>
#include <Core/Logger.h>
#include <stdlib.h>
#include <string.h>

// Thread worker function
static int asset_loader_thread(void *data) {
    AssetManager *manager = (AssetManager *) data;

    LOG_INFO("Asset loader thread started");

    while (!manager->shutdown) {
        SDL_LockMutex(manager->queue_mutex);

        // Wait for work or shutdown signal
        while (manager->job_count == 0 && !manager->shutdown) {
            SDL_WaitCondition(manager->queue_condition, manager->queue_mutex);
        }

        if (manager->shutdown) {
            SDL_UnlockMutex(manager->queue_mutex);
            break;
        }

        // Get the first job
        LoadJob job = manager->jobs[0];

        // Remove job from queue
        for (int i = 0; i < manager->job_count - 1; i++) {
            manager->jobs[i] = manager->jobs[i + 1];
        }
        manager->job_count--;

        SDL_UnlockMutex(manager->queue_mutex);

        // Load texture directly using IMG_LoadTexture - NO SURFACE INTERMEDIATE
        LOG_DEBUG("Loading texture '%s' from: %s", job.id, job.filepath);

        SDL_Texture *sdl_texture = IMG_LoadTexture(manager->renderer, job.filepath);
        if (!sdl_texture) {
            LOG_ERROR("Failed to load texture '%s' from %s: %s",
                      job.id, job.filepath, SDL_GetError());
            continue;
        }

        LOG_DEBUG("Texture '%s' loaded successfully", job.id);

        // Lock to update job status
        SDL_LockMutex(manager->queue_mutex);

        // Find the job entry and mark it as complete with the texture result
        for (int i = 0; i < manager->job_count; i++) {
            if (strcmp(manager->jobs[i].id, job.id) == 0) {
                manager->jobs[i].result_texture = sdl_texture;
                manager->jobs[i].completed = true;
                LOG_DEBUG("Job '%s' marked as completed with texture result", job.id);
                break;
            }
        }

        SDL_UnlockMutex(manager->queue_mutex);
    }

    LOG_INFO("Asset loader thread finished");
    return 0;
}


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

    manager->renderer = renderer;

    // Initialize texture cache
    manager->capacity = 32;
    manager->textures = malloc(sizeof(Texture *) * manager->capacity);
    if (!manager->textures) {
        LOG_CRITICAL("AssetManager_Create failed: could not allocate texture array");
        free(manager);
        return NULL;
    }
    memset(manager->textures, 0, sizeof(Texture *) * manager->capacity);
    manager->count = 0;

    // Initialize job queue
    manager->job_capacity = 16;
    manager->jobs = malloc(sizeof(LoadJob) * manager->job_capacity);
    if (!manager->jobs) {
        LOG_CRITICAL("AssetManager_Create failed: could not allocate job queue");
        free(manager->textures);
        free(manager);
        return NULL;
    }
    memset(manager->jobs, 0, sizeof(LoadJob) * manager->job_capacity);
    manager->job_count = 0;

    // Create synchronization primitives
    manager->queue_mutex = SDL_CreateMutex();
    if (!manager->queue_mutex) {
        LOG_CRITICAL("AssetManager_Create failed: could not create mutex");
        free(manager->jobs);
        free(manager->textures);
        free(manager);
        return NULL;
    }

    manager->queue_condition = SDL_CreateCondition();
    if (!manager->queue_condition) {
        LOG_CRITICAL("AssetManager_Create failed: could not create condition");
        SDL_DestroyMutex(manager->queue_mutex);
        free(manager->jobs);
        free(manager->textures);
        free(manager);
        return NULL;
    }

    manager->shutdown = false;

    // Start loader thread
    manager->loader_thread = SDL_CreateThread(asset_loader_thread, "AssetLoader", manager);
    if (!manager->loader_thread) {
        LOG_CRITICAL("AssetManager_Create failed: could not create loader thread");
        SDL_DestroyCondition(manager->queue_condition);
        SDL_DestroyMutex(manager->queue_mutex);
        free(manager->jobs);
        free(manager->textures);
        free(manager);
        return NULL;
    }

    LOG_INFO("AssetManager created with loader thread");
    return manager;
}


void AssetManager_LoadTextureAsync(AssetManager *manager,
                                   const char *filepath,
                                   const char *id,
                                   float x, float y, float scale) {
    if (!manager || !filepath || !id) {
        LOG_ERROR("AssetManager_LoadTextureAsync: invalid parameters");
        return;
    }

    // Check if already loaded
    if (AssetManager_GetTexture(manager, id)) {
        LOG_WARN("AssetManager_LoadTextureAsync: texture '%s' already loaded, skipping", id);
        return;
    }

    LOG_DEBUG("Queuing async load for '%s' from: %s", id, filepath);

    SDL_LockMutex(manager->queue_mutex);

    // Grow job queue if needed
    if (manager->job_count >= manager->job_capacity) {
        manager->job_capacity *= 2;
        LoadJob *new_jobs = realloc(manager->jobs, sizeof(LoadJob) * manager->job_capacity);
        if (!new_jobs) {
            LOG_ERROR("AssetManager_LoadTextureAsync: failed to grow job queue");
            SDL_UnlockMutex(manager->queue_mutex);
            return;
        }
        manager->jobs = new_jobs;
        LOG_DEBUG("Job queue grown to capacity: %d", manager->job_capacity);
    }

    // Add job to queue
    LoadJob *job = &manager->jobs[manager->job_count];
    strncpy(job->filepath, filepath, sizeof(job->filepath) - 1);
    job->filepath[sizeof(job->filepath) - 1] = '\0';
    strncpy(job->id, id, sizeof(job->id) - 1);
    job->id[sizeof(job->id) - 1] = '\0';
    job->x = x;
    job->y = y;
    job->scale = scale;
    job->result_texture = NULL;
    job->completed = false;
    job->failed = false;

    manager->job_count++;

    // Signal the loader thread
    SDL_SignalCondition(manager->queue_condition);
    SDL_UnlockMutex(manager->queue_mutex);

    LOG_DEBUG("Job queued for '%s', queue size: %d", id, manager->job_count);
}


void AssetManager_PollResults(AssetManager *manager) {
    if (!manager) return;

    SDL_LockMutex(manager->queue_mutex);

    // Check for completed jobs
    for (int i = 0; i < manager->job_count; i++) {
        LoadJob *job = &manager->jobs[i];

        if (job->completed && job->result_texture) {
            LOG_DEBUG("Found completed job: '%s'", job->id);

            // Create Texture wrapper using the Texture class
            Texture *texture = Texture_Create(
                job->id,
                job->result_texture,
                job->x,
                job->y,
                job->scale
            );

            if (!texture) {
                LOG_ERROR("Failed to create Texture wrapper for '%s'", job->id);
                SDL_DestroyTexture(job->result_texture);
                goto skip_job;
            }

            // Add to cache
            if (manager->count >= manager->capacity) {
                manager->capacity *= 2;
                Texture **new_textures = realloc(manager->textures,
                                                 sizeof(Texture *) * manager->capacity);
                if (!new_textures) {
                    LOG_CRITICAL("Failed to grow texture cache");
                    Texture_Destroy(texture);
                    SDL_DestroyTexture(job->result_texture);
                    goto skip_job;
                }
                manager->textures = new_textures;
                LOG_DEBUG("Texture cache grown to capacity: %d", manager->capacity);
            }

            manager->textures[manager->count] = texture;
            manager->count++;

            LOG_INFO("Texture '%s' added to cache (total: %d)", job->id, manager->count);

            skip_job:
            // Remove completed job from queue
            for (int j = i; j < manager->job_count - 1; j++) {
                manager->jobs[j] = manager->jobs[j + 1];
            }
            manager->job_count--;
            i--;  // Recheck this position
        }
    }

    SDL_UnlockMutex(manager->queue_mutex);
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

            // Destroy the Texture wrapper (doesn't destroy SDL_Texture)
            Texture_Destroy(manager->textures[i]);

            // Manually destroy the SDL_Texture
            SDL_Texture *sdl_tex = manager->textures[i]->texture;
            if (sdl_tex) {
                SDL_DestroyTexture(sdl_tex);
            }

            // Remove from cache
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
    LOG_INFO("Pending jobs: %d/%d", manager->job_count, manager->job_capacity);

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

    // Signal thread to shutdown
    SDL_LockMutex(manager->queue_mutex);
    manager->shutdown = true;
    SDL_SignalCondition(manager->queue_condition);
    SDL_UnlockMutex(manager->queue_mutex);

    // Wait for thread to finish
    SDL_WaitThread(manager->loader_thread, NULL);
    LOG_DEBUG("Asset loader thread joined");

    // Destroy all textures
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
    free(manager->jobs);
    SDL_DestroyCondition(manager->queue_condition);
    SDL_DestroyMutex(manager->queue_mutex);
    free(manager);

    LOG_DEBUG("AssetManager destroyed");
}
