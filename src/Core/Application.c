#include <stdlib.h>
#include <Core/Application.h>
#include <Core/Logger.h>
#include <Scene/Menu.h>
#include <Scene/SceneManager.h>
#include <SDL3/SDL.h>

Application Application_Create(void) {
    LOG_INFO("Creating Application");

    Application application = {0};
    application.window = NULL;
    application.renderer = NULL;
    application.scene_manager = NULL;
    application.asset_manager = NULL;
    application.game_time = (GameTime){0};
    application.input = (InputSystem){0};
    application.running = true;
    application.assets_loaded = false;

    return application;
}

void Application_Initialize(Application *application) {
    if (!application) {
        LOG_CRITICAL("Application_Initialize: application is NULL");
        return;
    }

    LOG_INFO("Initializing Application");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_CRITICAL("SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_Init() succeeded");

    application->window = SDL_CreateWindow("Fizzle Framework", 1600, 900, 0);
    if (!application->window) {
        LOG_CRITICAL("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_CreateWindow() succeeded");

    application->renderer = SDL_CreateRenderer(application->window, NULL);
    if (!application->renderer) {
        LOG_CRITICAL("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_CreateRenderer() succeeded");

    GameTime_Init(&application->game_time);
    Input_Init(&application->input);

    application->asset_manager = AssetManager_Create(application->renderer);
    if (!application->asset_manager) {
        LOG_CRITICAL("Failed to create AssetManager");
        SDL_DestroyRenderer(application->renderer);
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("AssetManager created");

    application->scene_manager = SceneManager_Create(application->renderer, application->asset_manager);
    if (!application->scene_manager) {
        LOG_CRITICAL("Failed to create SceneManager");
        AssetManager_Destroy(application->asset_manager);
        SDL_DestroyRenderer(application->renderer);
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SceneManager created");

    Scene *menu_scene = MenuScene_Create_Instance();
    if (!menu_scene) {
        LOG_CRITICAL("Failed to create MenuScene");
        SceneManager_Destroy(application->scene_manager);
        AssetManager_Destroy(application->asset_manager);
        SDL_DestroyRenderer(application->renderer);
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SceneManager_AddScene(application->scene_manager, menu_scene);
    LOG_DEBUG("MenuScene created and registered");

    LOG_INFO("Application_Initialized successfully");
}

void Application_Run(Application *application) {
    if (!application) {
        LOG_ERROR("Application_Run: application is NULL");
        return;
    }

    LOG_INFO("Running Application");

    // Switch to menu scene (loads assets synchronously)
    Scene *menu_scene = application->scene_manager->scenes[0];
    if (menu_scene) {
        SceneManager_SwitchScene(application->scene_manager, menu_scene);
        LOG_DEBUG("Switched to MenuScene");
    }

    AssetManager_PrintStats(application->asset_manager);
    application->assets_loaded = true;

    // Main game loop
    while (application->running) {
        GameTime_Tick(&application->game_time);
        Input_Update(&application->input);

        Application_Update(application);
        Application_Render(application);
    }

    LOG_INFO("Application loop ended");
}

void Application_Update(Application *application) {
    if (!application) return;

    if (Input_KeyHeld(&application->input, KEY_ESCAPE)) {
        application->running = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            application->running = false;
        }
    }

    if (application->scene_manager) {
        SceneManager_Update(application->scene_manager, &application->game_time.elapsed_time);
    }
}

void Application_Render(const Application *application) {
    if (!application || !application->renderer) return;

    SDL_SetRenderDrawColor(application->renderer, 255, 0, 147, 255);
    SDL_RenderClear(application->renderer);

    if (application->scene_manager) {
        SceneManager_Render(application->scene_manager);
    }

    SDL_RenderPresent(application->renderer);
}

void Application_Destroy(Application *application) {
    if (!application) return;

    LOG_INFO("Destroying Application");

    GameTime_Shutdown(&application->game_time);

    if (application->scene_manager) {
        SceneManager_Destroy(application->scene_manager);
    }

    if (application->asset_manager) {
        AssetManager_Destroy(application->asset_manager);
    }

    if (application->renderer) {
        SDL_DestroyRenderer(application->renderer);
    }

    if (application->window) {
        SDL_DestroyWindow(application->window);
    }

    SDL_Quit();
    LOG_INFO("Application Destroyed");
}
