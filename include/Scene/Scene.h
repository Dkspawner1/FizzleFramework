#ifndef FIZZLEFRAMEWORK_SCENE_H
#define FIZZLEFRAMEWORK_SCENE_H
#include <stdlib.h>

typedef struct Scene {
    char *name;

    void (*create)(void);

    void (*initialize)(void);

    void (*load_assets)(AssetManager *asset_manager); // ✅ Pass AssetManager
    void (*update)(float deltatime);

    void (*render)(SDL_Renderer *renderer, AssetManager *asset_manager); // ✅ Pass both
    void (*destroy)(void);

    AssetManager *asset_manager;
} Scene;

static inline void Scene_Destroy(Scene *scene) {
    if (!scene) return;
    if (scene->destroy) {
        scene->destroy();
    }
    if (scene->name) {
        free(scene->name);
    }
    free(scene);
}


#endif //FIZZLEFRAMEWORK_SCENE_H
