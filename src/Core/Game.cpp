#include <iostream>
#include <thread>
#include <Core/Game.h>

Game::Game() : graphics(std::make_unique<GraphicsDeviceManager>("FizzleFramework", 1600, 900)),
               content(std::make_unique<ContentManager>()),
               spriteBatch(nullptr) {
}

Game::~Game() = default;

void Game::Run() {
    Initialize();
    LoadContent();

    // You can change this value to adjust the target frame rate
    constexpr float targetFPS = 60.0f; // Change this to 144.0f for 144 FPS
    constexpr float targetFrameTime = 1.0f / targetFPS; // Time per frame in seconds

    while (!graphics->GetWindow()->ShouldClose()) {
        auto frameStartTime = std::chrono::steady_clock::now(); // Start timing the frame

        gameTime.Update();
        graphics->GetWindow()->PollEvents();
        Update(gameTime);

        graphics->BeginDraw();
        Draw();
        graphics->EndDraw();

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
    graphics->Initialize();
    spriteBatch = std::make_unique<SpriteBatch>(graphics->GetRenderer());
}

void Game::LoadContent() {
}

void Game::Update(GameTime &gameTime) {
}

void Game::Draw() {
}
