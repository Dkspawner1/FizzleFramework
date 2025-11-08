#include <stdlib.h>
#include <string.h>
#include <Core/AssetManager.h>
#include <Core/Logger.h>
#include <Scene/Menu.h>
#include <Scene/Scene.h>
#include <SDL3/SDL_render.h>

static const char *get_asset_path(const char *filename) {
    static char paths[8][512];
    static int index = 0;

    if (!filename) {
        LOG_ERROR("get_asset_path: filename is NULL");
        return "";
    }

    index = (index + 1) % 8;
    snprintf(paths[index], sizeof(paths[index]), "%s/%s", ASSETS_DIR, filename);

    LOG_DEBUG("Asset path: %s", paths[index]);
    return paths[index];
}



void MenuScene_Create(void) {
    LOG_DEBUG("Creating Menu Scene");
}

void MenuScene_Initialize(void) {
    LOG_DEBUG("Initializing Menu Scene");
}

void MenuScene_LoadAssets(AssetManager *asset_manager) {
    LOG_DEBUG("Loading Menu Scene Assets");

    if (!asset_manager) {
        LOG_WARN("MenuScene_LoadAssets: AssetManager is NULL");
        return;
    }

    LOG_INFO("Queuing Menu assets for async loading...");

    // Queue all textures for async loading
    AssetManager_LoadTexture(asset_manager,
                                  get_asset_path("Board.png"),
                                  "board", 0, 0, 1.0f);

    AssetManager_LoadTexture(asset_manager,
                                  get_asset_path("Ball.png"),
                                  "ball", 750, 425, 2.0f);

    AssetManager_LoadTexture(asset_manager,
                                  get_asset_path("Computer.png"),
                                  "player_paddle", 10, 350, 2.0f);

    AssetManager_LoadTexture(asset_manager,
                                  get_asset_path("Player.png"),
                                  "cpu_paddle", 1560, 350, 2.0f);

    LOG_INFO("Menu asset jobs queued");
}

void MenuScene_Update(float deltatime) {
    // Menu update logic here
    (void) deltatime;  // Unused for now
}

void MenuScene_Render(SDL_Renderer *renderer, AssetManager *asset_manager) {
    if (!renderer || !asset_manager) {
        LOG_WARN("MenuScene_Render: renderer or asset_manager is NULL");
        return;
    }

    // Render all textures
    Texture *board = AssetManager_GetTexture(asset_manager, "board");
    if (board) {
        SDL_FRect rect = Texture_GetRect(board);
        SDL_RenderTexture(renderer, Texture_GetSDLTexture(board), NULL, &rect);
    }

    Texture *ball = AssetManager_GetTexture(asset_manager, "ball");
    if (ball) {
        SDL_FRect rect = Texture_GetRect(ball);
        SDL_RenderTexture(renderer, Texture_GetSDLTexture(ball), NULL, &rect);
    }

    Texture *player_paddle = AssetManager_GetTexture(asset_manager, "player_paddle");
    if (player_paddle) {
        SDL_FRect rect = Texture_GetRect(player_paddle);
        SDL_RenderTexture(renderer, Texture_GetSDLTexture(player_paddle), NULL, &rect);
    }

    Texture *cpu_paddle = AssetManager_GetTexture(asset_manager, "cpu_paddle");
    if (cpu_paddle) {
        SDL_FRect rect = Texture_GetRect(cpu_paddle);
        SDL_RenderTexture(renderer, Texture_GetSDLTexture(cpu_paddle), NULL, &rect);
    }
}

void MenuScene_Destroy(void) {
    LOG_DEBUG("Destroying Menu Scene");
}

Scene *MenuScene_Create_Instance(void) {
    Scene *scene = (Scene *) malloc(sizeof(Scene));
    if (!scene) {
        LOG_ERROR("MenuScene_Create_Instance: Failed to allocate Scene");
        return NULL;
    }

    scene->name = (char *) malloc(strlen("MenuScene") + 1);
    if (!scene->name) {
        LOG_ERROR("MenuScene_Create_Instance: Failed to allocate name");
        free(scene);
        return NULL;
    }
    strcpy(scene->name, "MenuScene");

    scene->create = MenuScene_Create;
    scene->initialize = MenuScene_Initialize;
    scene->load_assets = MenuScene_LoadAssets;
    scene->update = MenuScene_Update;
    scene->render = MenuScene_Render;
    scene->destroy = MenuScene_Destroy;
    scene->asset_manager = NULL;  // Will be set by SceneManager

    return scene;
}
