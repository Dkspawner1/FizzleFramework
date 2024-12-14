#include <Game/Game1.h>
void Game1::Initialize() {
    Game::Initialize();

    m_inputManager = std::make_unique<InputManager>(GetWindow()->GetGLFWWindow());
    m_sceneManager->ChangeToLoadingScene();
}

void Game1::LoadContent() {
    Game::LoadContent();
}

void Game1::Update(GameTime &gameTime) {
    m_sceneManager->Update(gameTime);
}

void Game1::Draw() {
    m_sceneManager->Draw();
}
