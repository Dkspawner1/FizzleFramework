#ifndef FIZZLEFRAMEWORK_SCENE_MANAGER_H
#define FIZZLEFRAMEWORK_SCENE_MANAGER_H
#include <Core/AssetManager.h>
#include <Core/GameTime.h>
#include <Scene/Scene.h>
#include <SDL3/SDL_render.h>

typedef struct SceneManager {
    Scene **scenes;
    int count;
    int capacity;
    Scene *current_scene;
    SDL_Renderer *renderer;
    AssetManager *asset_manager;
} SceneManager;

SceneManager *SceneManager_Create(SDL_Renderer *renderer, AssetManager *asset_manager);

void SceneManager_AddScene(SceneManager *manager, Scene *scene);

void SceneManager_LoadScene(SceneManager *manager, Scene *scene);

void SceneManager_SwitchScene(SceneManager *manager, Scene *scene);

void SceneManager_Update(SceneManager *manager, float *deltatime);

void SceneManager_Render(SceneManager *manager);

void SceneManager_UnloadScene(SceneManager *manager, Scene *scene);

void SceneManager_Destroy(SceneManager *manager);

#endif //FIZZLEFRAMEWORK_SCENE_MANAGER_H
