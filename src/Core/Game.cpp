#include <Core/Game.h>

Game::Game(): graphics(nullptr), content(nullptr), spriteBatch(nullptr) {
}
Game::~Game() = default;

void Game::Run() {
    Initialize();
    LoadContent();

    while (true) {
        gameTime.Update();
        Update(gameTime);
        Draw();
    }
}
void Game::Initialize() {

}
void Game::LoadContent() {

}
void Game::Update(GameTime &gameTime) {

}
void Game::Draw() {

}



