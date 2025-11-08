#include <Core/Application.h>
#include <Core/Logger.h>
#include <stdlib.h>
#include <SDL3_image/SDL_image.h>
#include <math.h>

#include "Scene/Menu.h"

// Helper function to build asset path
static const char *get_asset_path(const char *filename) {
    static char paths[8][512];
    static int index = 0;

    index = (index + 1) % 8;

    // Build path using ASSETS_DIR macro
    snprintf(paths[index], sizeof(paths[index]), "%s/%s", ASSETS_DIR, filename);

    return paths[index];
}

Application Application_Create(void) {
    LOG_INFO("Creating Application");

    Application application = {0};
    application.window = NULL;
    application.renderer = NULL;
    application.game_time = (GameTime){0};
    application.running = true;

    return application;
}

void Application_Initialize(Application *application) {
    LOG_INFO("Initializing Application");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_ERROR("SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_Init() Succeeded");

    application->window = SDL_CreateWindow("Fizzle Framework", 1600, 900, 0);
    if (!application->window) {
        LOG_ERROR("SDL_CreateWindow failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_CreateWindow() Succeeded");

    application->renderer = SDL_CreateRenderer(application->window, NULL);
    if (!application->renderer) {
        LOG_ERROR("SDL_CreateRenderer failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_CreateRenderer() Succeeded");

    GameTime_Init(&application->game_time);
    Input_Init(&application->input);

    application->asset_manager = AssetManager_Create(application->renderer);
    if (!application->asset_manager) {
        LOG_CRITICAL("Failed to create AssetManager");
        exit(EXIT_FAILURE);
    }

    application->scene_manager = SceneManager_Create(application->renderer);
    if (!application->scene_manager) {
        LOG_CRITICAL("Failed to create SceneManager");
        exit(EXIT_FAILURE);
    }

    // Create and register the menu scene
    Scene *menu_scene = MenuScene_Create_Instance();
    if (menu_scene) {
        SceneManager_AddScene(application->scene_manager, menu_scene);
        SceneManager_SwitchScene(application->scene_manager, menu_scene);
    } else {
        LOG_CRITICAL("Failed to create MenuScene");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Application_Initialized");
}

void Application_LoadAssets(Application *application) {
    LOG_INFO("Loading Assets");
    LOG_DEBUG("Asset directory: %s", ASSETS_DIR);

    // Queue async loads (non-blocking, returns immediately)
    AssetManager_LoadTextureAsync(application->asset_manager,
                                  get_asset_path("assets/board.png"),
                                  "board", 0, 0, 1.0f);

    AssetManager_LoadTextureAsync(application->asset_manager,
                                  get_asset_path("assets/ball.png"),
                                  "ball", 750, 425, 2.0f);

    AssetManager_LoadTextureAsync(application->asset_manager,
                                  get_asset_path("assets/computer.png"),
                                  "player_paddle", 10, 350, 2.0f);

    AssetManager_LoadTextureAsync(application->asset_manager,
                                  get_asset_path("assets/player.png"),
                                  "cpu_paddle", 1560, 350, 2.0f);

    LOG_INFO("Asset loading queued (async, non-blocking)");
}


void Application_Run(Application *application) {
    LOG_INFO("Running Application");

    while (application->running) {
        GameTime_Tick(&application->game_time);
        Input_Update(&application->input);

        AssetManager_PollResults(application->asset_manager);

        Application_Update(application);

        // Add scene update
        SceneManager_Update(application->scene_manager, &application->game_time.elapsed_time);

        Application_Render(application);
    }
}

void Application_Update(Application *application) {
    const float delta = application->game_time.elapsed_time;

    if (Input_KeyHeld(&application->input, KEY_ESCAPE)) {
        application->running = false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            application->running = false;
        }
    }
}

void Application_Render(const Application *application) {
    SDL_SetRenderDrawColor(application->renderer, 255, 0, 147, 255);
    SDL_RenderClear(application->renderer);

    // Render the current scene
    SceneManager_Render(application->scene_manager);

    SDL_RenderPresent(application->renderer);
}

void Application_Destroy(Application *application) {
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
