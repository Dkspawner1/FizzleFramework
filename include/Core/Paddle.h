#ifndef FIZZLEFRAMEWORK_PADDLE_H
#define FIZZLEFRAMEWORK_PADDLE_H
#include <Input.h>
#include <Logger.h>
#include <SDL3/SDL_render.h>

typedef struct Paddle {
    float speed;
    SDL_Texture *texture;
    SDL_FRect rect;
} Paddle;

static inline Paddle Paddle_Create(void) {
    LOG_DEBUG("Creating Paddle");
    return (Paddle){0};
}

static inline void Paddle_Reset_CPU(Paddle *paddle) {
    LOG_INFO("Resetting CPU Paddle");
    const float PADDLE_MARGIN = 10.0f;
    paddle->rect.y = (900 - paddle->rect.h) / 2.0f;
    paddle->rect.x = PADDLE_MARGIN;
}

static inline void Paddle_Reset_Player(Paddle *paddle) {
    LOG_INFO("Resetting Player Paddle");
    const float PADDLE_MARGIN = 10.0f;
    paddle->rect.y = (900 - paddle->rect.h) / 2.0f;
    paddle->rect.x = 1600 - paddle->rect.w - PADDLE_MARGIN;
}

static inline void Paddle_Clamp(Paddle *paddle, float screen_height) {
    if (paddle->rect.y < 0) {
        paddle->rect.y = 0;
    }
    if (paddle->rect.y + paddle->rect.h > screen_height) {
        paddle->rect.y = screen_height - paddle->rect.h;
    }
}

static inline void Paddle_Update_CPU(Paddle *paddle, const Ball *ball, float delta) {
    const float ball_center_y = ball->rect.y + ball->rect.h / 2.0f;
    const float paddle_center_y = paddle->rect.y + paddle->rect.h / 2.0f;

    if (ball_center_y > paddle_center_y + 15.0f) {
        paddle->rect.y += paddle->speed * delta;
    } else if (ball_center_y < paddle_center_y - 15.0f) {
        paddle->rect.y -= paddle->speed * delta;
    }
}

static inline void Paddle_Update_Player(Paddle *paddle, InputSystem *input, float delta) {
    if (Input_KeyHeld(input, KEY_UP)) {
        paddle->rect.y -= paddle->speed * delta;
    }
    if (Input_KeyHeld(input, KEY_DOWN)) {
        paddle->rect.y += paddle->speed * delta;
    }
}

static inline void Paddle_Destroy(const Paddle *paddle) {
    LOG_DEBUG("Destroying Paddle");
    if (paddle->texture) {
        SDL_DestroyTexture(paddle->texture);
    }
}

#endif //FIZZLEFRAMEWORK_PADDLE_H
