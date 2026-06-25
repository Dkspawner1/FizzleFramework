#pragma once

#include <debug/logger.h>
#include <SDL3/SDL.h>
#include <graphics/GraphicsDevice.h>

class Application
{
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    void Run();

    Uint32 g_WINDOW_WIDTH = 1600;
    Uint32 g_WINDOW_HEIGHT = 900;

private:
    [[nodiscard]] bool initialize();
    [[nodiscard]] bool load_assets();
    void handle_events();
    void update();
    void render();

    SDL_Window* m_window = nullptr;
    Fizzle::GraphicsDevice m_graphics_device;   // ← namespace prefix required

    bool   m_running = false;
    Uint64 m_performance_last = 0;
    Uint64 m_performance_frequency = 0;
    double m_delta_time = 0.0;
};