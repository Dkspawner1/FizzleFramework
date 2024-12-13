#include <Scenes/MenuScene.h>
#include <iostream>
#include <filesystem>

MenuScene::MenuScene(Game1* game) : m_game(game) {}

void MenuScene::Initialize() {
    m_inputManager = std::make_unique<InputManager>(m_game->GetWindow()->GetGLFWWindow());
}

void MenuScene::LoadContent() {
    try {
        m_textures.push_back(std::make_unique<Texture>(ContentManager::GetAssetPath("fizzle.png")));
        std::cout << "Texture loaded successfully" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Failed to load texture: " << e.what() << std::endl;
    }
}

void MenuScene::Update(GameTime &gameTime) {
    if (m_inputManager->IsKeyDown(GLFW_KEY_W)) {
        std::cout << "Main thread: Key W is pressed" << std::endl;
    }

    if (m_inputManager->IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        std::cout << "Main thread: Mouse button left is pressed" << std::endl;
    }

    auto mouseRect = m_inputManager->GetMousePosition();

    if (mouseRect.intersects(m_texRect)) {
        m_texColor = Color::DarkGray;
        if (m_inputManager->IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
            m_texColor = Color::Gray; // Change color on click
        }
    } else {
        m_texColor = Color::White;
    }
}

void MenuScene::Draw() {
    m_game->GetSpriteBatch()->Begin();

    // std::cout << "Drawing " << m_textures.size() << " textures" << std::endl;

    for (const auto &texture : m_textures) {
        if (texture) {
            m_game->GetSpriteBatch()->Draw(*texture, m_texRect, m_texColor);
            // std::cout << "Drew texture" << std::endl;
        } else {
            std::cout << "Null texture encountered" << std::endl;
        }
    }

    m_game->GetSpriteBatch()->End();
}

void MenuScene::UnloadContent() {
    // Unload any content specific to this scene if necessary
}
