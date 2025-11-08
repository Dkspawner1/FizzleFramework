#ifndef FIZZLEFRAMEWORK_APPLICATION_H
#define FIZZLEFRAMEWORK_APPLICATION_H

#include <stdbool.h>
#include <Core/AssetManager.h>
#include <Core/GameTime.h>
#include <Core/Input.h>
#include <SDL3/SDL.h>

#include "Scene/SceneManager.h"

typedef struct Application {
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameTime game_time;
    InputSystem input;

    AssetManager *asset_manager;
    SceneManager *scene_manager;

    bool running;
} Application;

Application Application_Create(void);

void Application_Initialize(Application *application);

void Application_LoadAssets(Application *application);

void Application_Run(Application *application);

void Application_Update(Application *application);

void Application_Render(const Application *application);

void Application_Destroy(Application *application);

#endif //FIZZLEFRAMEWORK_APPLICATION_H
