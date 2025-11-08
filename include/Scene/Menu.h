#ifndef FIZZLEFRAMEWORK_MENU_H
#define FIZZLEFRAMEWORK_MENU_H
#include <Core/AssetManager.h>
#include <SDL3/SDL_render.h>

typedef struct Scene Scene;

void MenuScene_Create(void);

void MenuScene_Initialize(void);

void MenuScene_LoadAssets(AssetManager *asset_manager);

void MenuScene_Update(float deltatime);

void MenuScene_Render(SDL_Renderer *renderer, AssetManager *asset_manager);

void MenuScene_Destroy(void);

Scene *MenuScene_Create_Instance(void);

#endif //FIZZLEFRAMEWORK_MENU_H
