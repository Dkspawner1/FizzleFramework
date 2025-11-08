#include <stdlib.h>
#include <Scene/SceneManager.h>

SceneManager *SceneManager_Create(SDL_Renderer *renderer) {
    if (renderer == NULL) {
        LOG_ERROR("SceneManager_Create failed: renderer cannot be NULL");
        return NULL;
    }
    SceneManager *manager = (SceneManager *) malloc(sizeof(SceneManager));
    manager->capacity = 3;
    manager->scenes = malloc(sizeof(Scene *) * manager->capacity);
    manager->count = 0;
    manager->current_scene = NULL; // ADD THIS LINE
    manager->renderer = renderer;
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
    scene->create();
    LOG_INFO("SceneManager_AddScene: added scene '%s'", scene->name);
}

void SceneManager_LoadScene(SceneManager *manager, Scene *scene) {
    if (!manager || !scene) return;
    LOG_INFO("Loading scene '%s'", scene->name);
    scene->load_assets();

    LOG_INFO("Scene '%s' loaded", scene->name);
}

void SceneManager_SwitchScene(SceneManager *manager, Scene *scene) {
    if (!manager || !scene) return;

    // Unload current scene if one is active
    if (manager->current_scene) {
        LOG_INFO("Unloading scene '%s'", manager->current_scene->name);
        manager->current_scene->destroy();
    }

    // Switch to new scene
    manager->current_scene = scene;
    LOG_INFO("Switched to scene '%s'", scene->name);

    // Initialize the new scene
    scene->initialize();
    scene->load_assets();
}

void SceneManager_Update(SceneManager *manager, float *deltatime) {
    if (!manager || !manager->current_scene) return;

    manager->current_scene->update(*deltatime);
}

void SceneManager_Render(SceneManager *manager) {
    if (!manager || !manager->current_scene) return;

    manager->current_scene->render();
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
    if (!manager)return;

    LOG_INFO("Destroying SceneManager");
    for (int i = 0; i < manager->count; i++) {
        Scene *scene = manager->scenes[i];
        Scene_Destroy(scene);
    }
    free(manager->scenes);
    free(manager);
    LOG_DEBUG("SceneManager destroyed");
}
