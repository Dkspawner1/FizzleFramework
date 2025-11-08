#ifndef FIZZLEFRAMEWORK_BALL_H
#define FIZZLEFRAMEWORK_BALL_H
#include <Logger.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL_render.h>

typedef struct Ball {
    SDL_Texture *texture;
    SDL_FRect rect;
    float velocity_x;
    float velocity_y;
} Ball;

static inline Ball Ball_Create(void) {
    LOG_DEBUG("Creating Ball");

    const float SERVE_SPEED = 500.0f;
    const float MIN_ANGLE = 30.0f * 0.0174533f; // 30° in radians
    const float MAX_ANGLE = 60.0f * 0.0174533f; // 60° in radians

    // Pick random angle
    float angle = MIN_ANGLE + (rand() / (float) RAND_MAX) * (MAX_ANGLE - MIN_ANGLE);

    // Pick random direction
    int direction = rand() % 2;

    // Calculate velocity based on direction and angle
    float velocity_x = cosf(angle) * SERVE_SPEED;
    float velocity_y = sinf(angle) * SERVE_SPEED * (rand() % 2 == 0 ? 1 : -1);

    // Flip velocity_x if going left
    if (direction == 0) {
        velocity_x = -velocity_x;
    }

    const Ball ball = {
        .velocity_x = velocity_x,
        .velocity_y = velocity_y,
        .texture = NULL,
        .rect = {0},
    };

    return ball;
}

static inline void Ball_Reset(Ball *ball) {
    LOG_INFO("Resetting Ball");

    const float SERVE_SPEED = 500.0f;
    const float MIN_ANGLE = 30.0f * 0.0174533f;
    const float MAX_ANGLE = 60.0f * 0.0174533f;

    float angle = MIN_ANGLE + (rand() / (float) RAND_MAX) * (MAX_ANGLE - MIN_ANGLE);
    int direction = rand() % 2;

    float velocity_x = cosf(angle) * SERVE_SPEED;
    float velocity_y = sinf(angle) * SERVE_SPEED * (rand() % 2 == 0 ? 1 : -1);

    if (direction == 0) {
        velocity_x = -velocity_x;
    }

    ball->velocity_x = velocity_x;
    ball->velocity_y = velocity_y;

    // Center ball on screen
    ball->rect.x = (1600 - ball->rect.w) / 2.0f;
    ball->rect.y = (900 - ball->rect.h) / 2.0f;
}

static inline void Ball_Update(Ball *ball, float delta) {
    ball->rect.x += ball->velocity_x * delta;
    ball->rect.y += ball->velocity_y * delta;

    // Bounce off top/bottom walls
    if (ball->rect.y < 0) {
        ball->rect.y = 0;
        ball->velocity_y = -ball->velocity_y;
    }
    if (ball->rect.y + ball->rect.h > 900) {
        ball->rect.y = 900 - ball->rect.h;
        ball->velocity_y = -ball->velocity_y;
    }
}

static inline bool Ball_OutOfBounds(const Ball *ball) {
    return ball->rect.x < 0 || ball->rect.x > 1600;
}

static inline void Ball_Destroy(Ball *ball) {
    LOG_DEBUG("Destroying Ball");
    if (ball->texture) {
        SDL_DestroyTexture(ball->texture);
    }
}

#endif //FIZZLEFRAMEWORK_BALL_H
