#include <iostream>
#include <Game/Game1.h>
#include <Core/Rectangle.h>
#include <Graphics/Color.h>
#include <Core/InputManager.h>

void Game1::Initialize() {
    Game::Initialize();
    m_inputManager = std::make_unique<InputManager>(graphics->GetWindow()->GetGLFWWindow());
    m_textures = std::vector<std::unique_ptr<Texture> >();
}

void Game1::LoadContent() {
    m_textures.push_back(std::make_unique<Texture>(ContentManager::GetAssetPath("fizzle.png")));
}

Color texColor = Color::White;
Rectangle texRect(200, 200, 400, 200);

void Game1::Update(GameTime &gameTime) {
    if (m_inputManager->IsKeyDown(GLFW_KEY_W)) {
        std::cout << "Key W is pressed" << std::endl;
    }
    if (m_inputManager->IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        std::cout << "Mouse button left is pressed" << std::endl;
    }
    auto mouseRect = m_inputManager->GetMousePosition();
    if (mouseRect.intersects(texRect)) {
        texColor = Color::DarkGray;
        if (m_inputManager->IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            texColor = Color::Gray;
        }
    } else texColor = Color::White;
}

void Game1::Draw() {
    spriteBatch->Begin();

    for (auto &texture: m_textures) {
        if (texture) {
            spriteBatch->Draw(*texture, texRect, texColor);
        }
    }

    spriteBatch->End();
}
