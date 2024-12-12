#include <Core/Game.h>

Game::Game() : graphics(std::make_unique<GraphicsDeviceManager>("FizzleFramework", 1600, 900)),
               content(std::make_unique<ContentManager>()),
               spriteBatch(nullptr) {
}

Game::~Game() = default;

void Game::Run() {
    Initialize();
    LoadContent();

    while (!graphics->GetWindow()->ShouldClose()) {
        gameTime.Update();
        graphics->GetWindow()->PollEvents();
        Update(gameTime);
        graphics->BeginDraw();
        Draw();
        graphics->EndDraw();
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
    spriteBatch->Begin();
    // Add drawing code here
    spriteBatch->End();
}
