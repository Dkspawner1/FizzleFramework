#include <Core/Input.h>
#include <Core/Logger.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

static SDL_Scancode keymap[KEY_COUNT] = {
    [KEY_UP] = SDL_SCANCODE_W,
    [KEY_DOWN] = SDL_SCANCODE_S,
    [KEY_ESCAPE] = SDL_SCANCODE_ESCAPE,
};

void Input_Init(InputSystem *input) {
    LOG_INFO("Initializing Input System");

    for (int i = 0; i < KEY_COUNT; i++) {
        input->keys[i].pressed = false;
        input->keys[i].held = false;
        input->keys[i].released = false;
    }
    LOG_DEBUG("Input System initialized");
}

void Input_Update(InputSystem *input) {
    // Clear per-frame states
    for (int i = 0; i < KEY_COUNT; i++) {
        input->keys[i].pressed = false;
        input->keys[i].released = false;
    }

    // Get keyboard state
    int num_keys;
    const bool *keyboard_state = SDL_GetKeyboardState(&num_keys);

    // Update all keys
    for (int i = 0; i < KEY_COUNT; i++) {
        const bool is_pressed = keyboard_state[keymap[i]];

        // Transition: not held -> pressed
        if (is_pressed && !input->keys[i].held) {
            input->keys[i].pressed = true;
            input->keys[i].held = true;
        }
        // Transition: held -> released
        else if (!is_pressed && input->keys[i].held) {
            input->keys[i].released = true;
            input->keys[i].held = false;
        }
    }
}

KeyState Input_GetKey(InputSystem *input, KeyAction key) {
    if (key >= KEY_COUNT) {
        LOG_WARN("Invalid key action: %d", key);
        return (KeyState){false, false, false};
    }
    return input->keys[key];
}

bool Input_KeyPressed(InputSystem *input, KeyAction key) {
    if (key >= KEY_COUNT) return false;
    return input->keys[key].pressed;
}

bool Input_KeyHeld(InputSystem *input, KeyAction key) {
    if (key >= KEY_COUNT) return false;
    return input->keys[key].held;
}

bool Input_KeyReleased(InputSystem *input, KeyAction key) {
    if (key >= KEY_COUNT) return false;
    return input->keys[key].released;
}
