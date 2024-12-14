#include <Game/Game1.h>
Game1::Game1() : Game(), m_jobSystem(std::make_unique<JobSystem>()) {
    m_sceneManager = std::make_unique<SceneManager>(this);
}
void Game1::Initialize() {
    Game::Initialize();
    m_inputManager = std::make_unique<InputManager>(GetWindow()->GetGLFWWindow());
    GetSceneManager()->ChangeScene("Loading");
}
void Game1::LoadContent() {
    Game::LoadContent();
}

void Game1::Update(GameTime &gameTime) {
    GetSceneManager()->Update(gameTime);
}

void Game1::Draw() {
    GetSceneManager()->Draw();
}