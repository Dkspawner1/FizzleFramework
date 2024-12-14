#include <Scenes/MenuScene.h>
#include <iostream>

void MenuScene::Initialize() {

    m_inputManager = std::make_unique<InputManager>(m_game->GetGraphicsDeviceManager()->GetWindow()->GetGLFWWindow());
    m_textureNames.push_back("fizzle.png");
}

void MenuScene::LoadContent() {
    for (const auto &textureName: m_textureNames) {
        try {
            m_game->GetContentManager()->ClaimAsset<Texture>(textureName);
            std::cout << "Texture " << textureName << " loaded successfully" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Failed to load texture " << textureName << ": " << e.what() << std::endl;
        }
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

    for (const auto &textureName: m_textureNames) {
        if (Texture *texture = m_game->GetContentManager()->Get<Texture>(textureName)) {
            m_game->GetSpriteBatch()->Draw(*texture, m_texRect, m_texColor);
        } else {
            std::cout << "Texture " << textureName << " not found" << std::endl;
        }
    }

    m_game->GetSpriteBatch()->End();
}

void MenuScene::UnloadContent() {
    for (const auto &textureName: m_textureNames) {
        m_game->GetContentManager()->ReleaseAsset(textureName);
    }
}
