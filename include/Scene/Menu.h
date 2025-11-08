#ifndef FIZZLEFRAMEWORK_MENU_H
#define FIZZLEFRAMEWORK_MENU_H

typedef struct Scene Scene;

void MenuScene_Create(void);

void MenuScene_Initialize(void);

void MenuScene_LoadAssets(void);

void MenuScene_Update(float deltatime);

void MenuScene_Render(void);

void MenuScene_Destroy(void);

Scene *MenuScene_Create_Instance(void);


#endif //FIZZLEFRAMEWORK_MENU_H
