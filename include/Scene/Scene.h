#ifndef FIZZLEFRAMEWORK_SCENE_H
#define FIZZLEFRAMEWORK_SCENE_H
#include <stdlib.h>

typedef struct Scene {
    char *name;

    void (*create)(void);

    void (*initialize)(void);

    void (*load_assets)(void);

    void (*update)(float deltatime);

    void (*render)(void);

    void (*destroy)(void);
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
