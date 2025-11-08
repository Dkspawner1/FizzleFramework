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

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        LOG_CRITICAL("SDL_Init failed: %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_Init() succeeded");

    // Create window
    application->window = SDL_CreateWindow("Fizzle Framework", 1600, 900, 0);
    if (!application->window) {
        LOG_CRITICAL("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_CreateWindow() succeeded");

    // Create renderer
    application->renderer = SDL_CreateRenderer(application->window, NULL);
    if (!application->renderer) {
        LOG_CRITICAL("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("SDL_CreateRenderer() succeeded");

    // Initialize game time
    GameTime_Init(&application->game_time);

    // Initialize input
    Input_Init(&application->input);

    // Create asset manager (starts loader thread)
    application->asset_manager = AssetManager_Create(application->renderer);
    if (!application->asset_manager) {
        LOG_CRITICAL("Failed to create AssetManager");
        SDL_DestroyRenderer(application->renderer);
        SDL_DestroyWindow(application->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    LOG_DEBUG("AssetManager created with loader thread");

    // Create scene manager
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

    // Create and register the menu scene
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

    // Switch to menu scene immediately (it will load assets)
    Scene *menu_scene = application->scene_manager->scenes[0];
    if (menu_scene) {
        SceneManager_SwitchScene(application->scene_manager, menu_scene);
        LOG_DEBUG("Switched to MenuScene");
    }

    // Main game loop
    while (application->running) {
        GameTime_Tick(&application->game_time);
        Input_Update(&application->input);

        // Poll for completed asset loads (background thread continues loading)
        AssetManager_PollResults(application->asset_manager);

        Application_Update(application);
        Application_Render(application);
    }

    LOG_INFO("Application loop ended");
}

void Application_Update(Application *application) {
    if (!application) return;

    // Check for escape key
    if (Input_KeyHeld(&application->input, KEY_ESCAPE)) {
        application->running = false;
    }

    // Process SDL events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                application->running = false;
                break;
            default:
                break;
        }
    }

    // Update scene
    if (application->scene_manager) {
        SceneManager_Update(application->scene_manager, &application->game_time.elapsed_time);
    }
}

void Application_Render(const Application *application) {
    if (!application || !application->renderer) return;

    // Clear with pink background
    SDL_SetRenderDrawColor(application->renderer, 255, 0, 147, 255);
    SDL_RenderClear(application->renderer);

    // Render scene
    if (application->scene_manager) {
        SceneManager_Render(application->scene_manager);
    }

    // Present
    SDL_RenderPresent(application->renderer);
}

void Application_Destroy(Application *application) {
    if (!application) return;

    LOG_INFO("Destroying Application");

    // Shutdown systems in reverse order of initialization
    GameTime_Shutdown(&application->game_time);
    LOG_DEBUG("GameTime shutdown");

    if (application->scene_manager) {
        SceneManager_Destroy(application->scene_manager);
        LOG_DEBUG("SceneManager destroyed");
    }

    if (application->asset_manager) {
        AssetManager_Destroy(application->asset_manager);  // Waits for loader thread
        LOG_DEBUG("AssetManager destroyed (loader thread joined)");
    }

    if (application->renderer) {
        SDL_DestroyRenderer(application->renderer);
        LOG_DEBUG("Renderer destroyed");
    }

    if (application->window) {
        SDL_DestroyWindow(application->window);
        LOG_DEBUG("Window destroyed");
    }

    SDL_Quit();
    LOG_INFO("Application Destroyed");
}
