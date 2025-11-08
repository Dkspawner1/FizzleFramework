#ifndef FIZZLEFRAMEWORK_ASSET_MANAGER_H
#define FIZZLEFRAMEWORK_ASSET_MANAGER_H
#include <Core/Texture.h>
#include <SDL3/SDL.h>

typedef struct {
    SDL_Renderer *renderer;
    Texture **textures;
    int count;
    int capacity;
} AssetManager;

AssetManager *AssetManager_Create(SDL_Renderer *renderer);

Texture *AssetManager_LoadTexture(AssetManager *manager,
                                  const char *filepath,
                                  const char *id,
                                  float x, float y, float scale);

Texture *AssetManager_GetTexture(AssetManager *manager, const char *id);

void AssetManager_UnloadTexture(AssetManager *manager, const char *id);

void AssetManager_PrintStats(const AssetManager *manager);

void AssetManager_Destroy(AssetManager *manager);

#endif //FIZZLEFRAMEWORK_ASSET_MANAGER_H
