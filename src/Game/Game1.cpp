#include <iostream>
#include <Game/Game1.h>
#include <Core/Rectangle.h>
#include <Graphics/Color.h>
#include <Core/InputManager.h>

void Game1::Initialize() {
    Game::Initialize();
    m_inputManager = std::make_unique<InputManager>(graphics->GetWindow()->GetGLFWWindow());
}

void Game1::LoadContent() {
    // Load game-specific content here
}

void Game1::Update(GameTime &gameTime) {
    if (m_inputManager->IsKeyDown(GLFW_KEY_W)) {
        std::cout << "Key W is pressed" << std::endl;
    }
    if (m_inputManager->IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        std::cout << "Mouse button left is pressed" << std::endl;
    }
    double mouseX, mouseY;
    m_inputManager->GetMousePosition(mouseX, mouseY);
    // std::cout << "Mouse X: " << mouseX << std::endl;
    // std::cout << "Mouse Y: " << mouseY << std::endl;
    // m_inputManager->SetMousePosition(100,100);

}

void Game1::Draw() {
    spriteBatch->Begin();
    Rectangle rect(0, 0, 200, 400);
    spriteBatch->Draw(rect, Color::Black);
    spriteBatch->End();
}//
