#include <Game/Game1.h>

Game1::~Game1() = default;

void Game1::Initialize() {
    Game::Initialize();

    // Initialize InputManager with the GLFW window
    m_inputManager = std::make_unique<InputManager>(GetWindow()->GetGLFWWindow());

    // Initialize SpriteBatch
    spriteBatch = std::make_unique<SpriteBatch>(graphics->GetRenderer());

    // Change to Loading Scene first before going to Menu or Game Scene
    m_sceneManager->ChangeToLoadingScene();

    // // Initialize the SceneManager and change to the initial scene (e.g., MenuScene)
    // m_sceneManager.ChangeScene("Menu");
}

void Game1::LoadContent() {
    // Load any global content if necessary
}

void Game1::Update(GameTime &gameTime) {
    m_sceneManager->Update(gameTime); // Update the current scene
}

void Game1::Draw() {
    m_sceneManager->Draw(); // Draw the current scene
}
