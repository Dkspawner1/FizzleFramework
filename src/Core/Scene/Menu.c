#include <stdlib.h>
#include <string.h>
#include <Core/Logger.h>
#include <Scene/Menu.h>

#include "Scene/Scene.h"

void MenuScene_Create(void) {
    LOG_DEBUG("Creating Menu Scene");
}

void MenuScene_Initialize(void) {
    LOG_DEBUG("Initializing Menu Scene");
}

void MenuScene_LoadAssets(void) {
    LOG_DEBUG("Loading Menu Scene Assets");
}

void MenuScene_Update(float deltatime) {
}

void MenuScene_Render(void) {
}

void MenuScene_Destroy(void) {
    LOG_DEBUG("Destroying Menu Scene");
}

Scene *MenuScene_Create_Instance(void) {
    Scene *scene = (Scene *) malloc(sizeof(Scene));
    scene->name = (char *) malloc(strlen("MenuScene") + 1);
    strcpy(scene->name, "MenuScene");

    scene->create = MenuScene_Create;
    scene->initialize = MenuScene_Initialize;
    scene->load_assets = MenuScene_LoadAssets;
    scene->update = MenuScene_Update;
    scene->render = MenuScene_Render;
    scene->destroy = MenuScene_Destroy;

    return scene;
}
