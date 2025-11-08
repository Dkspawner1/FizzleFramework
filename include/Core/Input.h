#ifndef FIZZLEFRAMEWORK_INPUT_H
#define FIZZLEFRAMEWORK_INPUT_H
#include <stdbool.h>

typedef enum {
    KEY_UP,
    KEY_DOWN,
    KEY_ESCAPE,
    KEY_COUNT
} KeyAction;

typedef struct {
    bool pressed;      // Pressed this frame
    bool held;         // Held for multiple frames
    bool released;     // Released this frame
} KeyState;
typedef struct {
    KeyState keys[KEY_COUNT];
} InputSystem;

void Input_Init(InputSystem *input);
void Input_Update(InputSystem *input);
KeyState Input_GetKey(InputSystem *input, KeyAction key);
bool Input_KeyPressed(InputSystem *input, KeyAction key);
bool Input_KeyHeld(InputSystem *input, KeyAction key);
bool Input_KeyReleased(InputSystem *input, KeyAction key);
#endif //FIZZLEFRAMEWORK_INPUT_H