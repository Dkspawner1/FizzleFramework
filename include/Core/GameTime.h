#ifndef FIZZLEFRAMEWORK_GAMETIME_H
#define FIZZLEFRAMEWORK_GAMETIME_H
#include <Core/Logger.h>
#include <stdint.h>
#include <SDL3/SDL_timer.h>

typedef struct GameTime {
    uint64_t last_time;
    uint64_t frequency;
    float elapsed_time;
    double total_time;
    uint64_t frame_count;
} GameTime;

static inline void GameTime_Init(GameTime *time) {
    time->frequency = SDL_GetPerformanceFrequency();
    time->last_time = SDL_GetPerformanceCounter();
    time->elapsed_time = 0.0f;
    time->total_time = 0.0;
    time->frame_count = 0;
    LOG_INFO("GameTime initialized");
}


static inline void GameTime_Tick(GameTime *time) {
    const uint64_t current_time = SDL_GetPerformanceCounter();
    const uint64_t delta_counter = current_time - time->last_time;
    float delta_time = (float) delta_counter / (float) time->frequency;

    if (delta_time > 0.25f) {
        delta_time = 0.25f;
    }

    time->last_time = current_time;
    time->elapsed_time = delta_time;
    time->total_time += delta_time;
    time->frame_count++;
}

/// JUST FOR LOGGING PURPOSES!
/// Since gametime is created on the stack,
/// it will be destroyed when the Application exits
static inline void GameTime_Shutdown(const GameTime *time) {
    LOG_INFO("GameTime shutdown (Total time: %.2f seconds, Frames: %llu)", time->total_time,
             (unsigned long long)time->frame_count);
}
#endif //FIZZLEFRAMEWORK_GAMETIME_H
