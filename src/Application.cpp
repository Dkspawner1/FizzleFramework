#include <Application.h>
#include <SDL3_shadercross/SDL_shadercross.h>

using namespace Fizzle::Debug;  // ← fixes Logger_Initialize, Logger_Shutdown, LogLevel

Application::Application()
{
    Logger_Initialize(LogLevel::DEBUG);
    LOG_INFO("Creating Application");
}

Application::~Application()
{
    LOG_INFO("Shutting down Application");
    m_graphics_device.Shutdown(m_window);

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
        LOG_INFO("Window destroyed");
    }

    SDL_Quit();
    LOG_INFO("SDL_Quit called");
    Logger_Shutdown();
}

bool Application::initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        LOG_ERROR("SDL_Init failed: {}", SDL_GetError());
        return false;
    }

    m_performance_frequency = SDL_GetPerformanceFrequency();
    m_performance_last = SDL_GetPerformanceCounter();

    m_window = SDL_CreateWindow(
        "FizzleFramework",
        1600, 900,
        SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY
    );
    if (!m_window)
    {
        LOG_ERROR("SDL_CreateWindow failed: {}", SDL_GetError());
        return false;
    }

    if (!m_graphics_device.Initialize(m_window))
        return false;

    if (!m_graphics_device.UploadGeometry())
        return false;

    SDL_ShowWindow(m_window);
    LOG_INFO("Window and GPU device ready");
    return true;
}

bool Application::load_assets()
{
    LOG_DEBUG("load_assets() complete");
    return true;
}

void Application::Run()
{
    if (!initialize())
    {
        LOG_CRITICAL("initialize() failed — aborting");
        return;
    }

    if (!load_assets())
    {
        LOG_CRITICAL("load_assets() failed — aborting");
        return;
    }

    m_running = true;
    LOG_INFO("Entering main loop");

    while (m_running)
    {
        handle_events();
        update();
        render();
    }
}

void Application::handle_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            LOG_INFO("SDL_EVENT_QUIT received");
            m_running = false;
            break;

        case SDL_EVENT_KEY_DOWN:
            if (event.key.key == SDLK_ESCAPE)
            {
                LOG_DEBUG("Escape pressed");
                m_running = false;
            }
            break;
        }
    }
}

void Application::update()
{
    const Uint64 now = SDL_GetPerformanceCounter();
    m_delta_time = static_cast<double>(now - m_performance_last)
        / static_cast<double>(m_performance_frequency);
    m_performance_last = now;

    LOG_TRACE("dt: {:.4f} ms", m_delta_time * 1000.0);
}

void Application::render()
{
    SDL_GPUCommandBuffer* cmd = SDL_AcquireGPUCommandBuffer(m_graphics_device.GetDevice());
    if (!cmd)
    {
        LOG_ERROR("SDL_AcquireGPUCommandBuffer failed: {}", SDL_GetError());
        return;
    }

    SDL_GPUTexture* swapchain = nullptr;
    SDL_WaitAndAcquireGPUSwapchainTexture(
        cmd, m_window, &swapchain, &g_WINDOW_WIDTH, &g_WINDOW_HEIGHT
    );

    if (swapchain)
    {
        SDL_GPUColorTargetInfo ct{};
        ct.texture = swapchain;
        ct.load_op = SDL_GPU_LOADOP_CLEAR;
        ct.store_op = SDL_GPU_STOREOP_STORE;
        ct.clear_color = { 1.0f, 0.0f, 0.577f, 1.0f };

        SDL_GPURenderPass* pass = SDL_BeginGPURenderPass(cmd, &ct, 1, nullptr);
        // draw calls go here
        SDL_EndGPURenderPass(pass);
    }

    SDL_SubmitGPUCommandBuffer(cmd);
}