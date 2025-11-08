#ifndef FIZZLEFRAMEWORK_ASSET_MANAGER_H
#define FIZZLEFRAMEWORK_ASSET_MANAGER_H
#include <Core/Texture.h>
#include <SDL3/SDL.h>
#include <stdbool.h>

// Load job
typedef struct {
    char filepath[512];
    char id[256];
    float x, y, scale;
    SDL_Texture *result_texture;
    bool completed;
    bool failed;
} LoadJob;

typedef struct AssetManager {
    SDL_Renderer *renderer;

    // Texture cache
    Texture **textures;
    int count;
    int capacity;

    // Job queue
    LoadJob *jobs;
    int job_count;
    int job_capacity;

    // Threading
    SDL_Thread *loader_thread;
    SDL_Mutex *queue_mutex;
    SDL_Condition *queue_condition;
    bool shutdown;
} AssetManager;

AssetManager *AssetManager_Create(SDL_Renderer *renderer);

void AssetManager_LoadTextureAsync(AssetManager *manager,
                                  const char *filepath,
                                  const char *id,
                                  float x, float y, float scale);

void AssetManager_PollResults(AssetManager *manager);

Texture *AssetManager_GetTexture(AssetManager *manager, const char *id);

void AssetManager_UnloadTexture(AssetManager *manager, const char *id);

void AssetManager_PrintStats(const AssetManager *manager);

void AssetManager_Destroy(AssetManager *manager);

#endif //FIZZLEFRAMEWORK_ASSET_MANAGER_H
