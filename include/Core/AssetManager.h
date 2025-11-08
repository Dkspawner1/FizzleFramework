#ifndef FIZZLEFRAMEWORK_ASSET_MANAGER_H
#define FIZZLEFRAMEWORK_ASSET_MANAGER_H
#include <Core/Texture.h>
#include <SDL3/SDL_asyncio.h>

typedef struct AssetManager {
    SDL_AsyncIOQueue *queue;
    Texture **textures;
    int count;
    int capacity;
    SDL_Renderer *renderer;
} AssetManager;

AssetManager *AssetManager_Create(SDL_Renderer *renderer);

// Queue async file load (non-blocking, returns immediately)
void AssetManager_LoadTextureAsync(AssetManager *manager,
                                   const char *filepath,
                                   const char *id,
                                   float x, float y, float scale);

// Poll for completed async I/O and upload to GPU (main thread only)
void AssetManager_PollResults(AssetManager *manager);

// Retrieve texture from cache (returns NULL if not loaded yet)
Texture *AssetManager_GetTexture(AssetManager *manager, const char *id);

bool AssetManager_IsLoadingComplete(AssetManager *manager);

// Unload a texture by ID (decrements refcount, frees if refcount == 0)
void AssetManager_UnloadTexture(AssetManager *manager, const char *id);

// Debug: print all loaded textures
void AssetManager_PrintStats(const AssetManager *manager);

void AssetManager_Destroy(AssetManager *manager);

#endif //FIZZLEFRAMEWORK_ASSET_MANAGER_H
