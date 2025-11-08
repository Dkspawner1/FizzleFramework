#include <stdlib.h>
#include <Scene/SceneManager.h>
#include <Core/Logger.h>

SceneManager *SceneManager_Create(SDL_Renderer *renderer, AssetManager *asset_manager) {
    if (renderer == NULL || asset_manager == NULL) {
        LOG_ERROR("SceneManager_Create failed: renderer and asset_manager cannot be NULL");
        return NULL;
    }

    SceneManager *manager = (SceneManager *) malloc(sizeof(SceneManager));
    if (!manager) {
        LOG_ERROR("SceneManager_Create: Failed to allocate memory");
        return NULL;
    }

    manager->capacity = 3;
    manager->scenes = malloc(sizeof(Scene *) * manager->capacity);
    if (!manager->scenes) {
        LOG_ERROR("SceneManager_Create: Failed to allocate scenes array");
        free(manager);
        return NULL;
    }

    manager->count = 0;
    manager->current_scene = NULL;
    manager->renderer = renderer;
    manager->asset_manager = asset_manager;

    LOG_INFO("SceneManager created (capacity=%d)", manager->capacity);
    return manager;
}

void SceneManager_AddScene(SceneManager *manager, Scene *scene) {
    if (!manager || !scene) return;

    if (manager->count >= manager->capacity) {
        LOG_WARN("SceneManager_AddScene: capacity reached, increasing capacity");
        manager->capacity *= 2;
        manager->scenes = realloc(manager->scenes, sizeof(Scene *) * manager->capacity);
    }

    manager->scenes[manager->count++] = scene;
    scene->asset_manager = manager->asset_manager;  // ✅ Assign AssetManager
    scene->create();
    LOG_INFO("SceneManager_AddScene: added scene '%s'", scene->name);
}

void SceneManager_LoadScene(SceneManager *manager, Scene *scene) {
    if (!manager || !scene) return;
    LOG_INFO("Loading scene '%s'", scene->name);
    scene->load_assets(manager->asset_manager);  // ✅ Pass AssetManager
    LOG_INFO("Scene '%s' loaded", scene->name);
}

void SceneManager_SwitchScene(SceneManager *manager, Scene *scene) {
    if (!manager || !scene) return;

    if (manager->current_scene) {
        LOG_INFO("Unloading scene '%s'", manager->current_scene->name);
        manager->current_scene->destroy();
    }

    manager->current_scene = scene;
    scene->asset_manager = manager->asset_manager;  // ✅ Assign AssetManager
    LOG_INFO("Switched to scene '%s'", scene->name);

    scene->initialize();
    scene->load_assets(manager->asset_manager);  // ✅ Pass AssetManager
}

void SceneManager_Update(SceneManager *manager, float *deltatime) {
    if (!manager || !manager->current_scene) return;
    manager->current_scene->update(*deltatime);
}

void SceneManager_Render(SceneManager *manager) {
    if (!manager || !manager->current_scene) return;

    manager->current_scene->render(manager->renderer, manager->asset_manager);  // ✅ Pass both
}

void SceneManager_UnloadScene(SceneManager *manager, Scene *scene) {
    if (!manager || !scene) return;

    LOG_INFO("Unloading scene '%s'", scene->name);

    if (manager->current_scene == scene) {
        manager->current_scene = NULL;
    }

    scene->destroy();
}

void SceneManager_Destroy(SceneManager *manager) {
    if (!manager) return;

    LOG_INFO("Destroying SceneManager");
    for (int i = 0; i < manager->count; i++) {
        Scene *scene = manager->scenes[i];
        if (scene) Scene_Destroy(scene);
    }
    free(manager->scenes);
    free(manager);
    LOG_DEBUG("SceneManager destroyed");
}
