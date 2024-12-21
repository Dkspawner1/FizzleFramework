#include <iostream>
#include <thread>
#include <Core/Game.h>
#include <Scenes/SceneManager.h>

Game::Game() : m_sceneManager(std::make_unique<SceneManager>(this)),
               m_graphics(std::make_unique<GraphicsDeviceManager>("FizzleFramework", 1600, 900)),
               m_contentManager(std::make_unique<ContentManager>()),
               m_spriteBatch(nullptr) {
}

Game::~Game() = default;

void Game::Exit() {
std::cout <<"Exit called" << std::endl;
}

void Game::Run() {
    Initialize();
    LoadContent();

    // You can change this value to adjust the target frame rate
    constexpr float targetFPS = 60.0f; // Change this to 144.0f for 144 FPS
    constexpr float targetFrameTime = 1.0f / targetFPS; // Time per frame in seconds

    while (!m_graphics->GetWindow()->ShouldClose()) {
        auto frameStartTime = std::chrono::steady_clock::now(); // Start timing the frame

        m_gameTime.Update();
        m_graphics->GetWindow()->PollEvents();
        Update(m_gameTime);

        m_graphics->BeginDraw();
        Draw();
        m_graphics->EndDraw();

        auto frameEndTime = std::chrono::steady_clock::now(); // End timing the frame
        std::chrono::duration<float> elapsedTime = frameEndTime - frameStartTime; // Calculate elapsed time

        float sleepTime = targetFrameTime - elapsedTime.count(); // Calculate how long to sleep
        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime)); // Sleep for remaining time
        } else {
            // Log or handle the case where the frame took too long
            std::cout << "Frame took too long: " << -sleepTime << " seconds" << std::endl;
        }
    }
}

void Game::Initialize() {
    m_graphics->Initialize();
    m_spriteBatch = std::make_unique<SpriteBatch>(m_graphics->GetRenderer());
}

void Game::LoadContent() {
}

void Game::Update(GameTime &gameTime) {
}

void Game::Draw() {
}
