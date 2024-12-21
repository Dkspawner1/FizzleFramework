#include <Scenes/MenuScene.h>
#include <iostream>
#include <ranges>

void MenuScene::Initialize() {
    m_inputManager = std::make_unique<InputManager>(m_game->GetGraphicsDeviceManager()->GetWindow()->GetGLFWWindow());
    m_textureNames.push_back("textures/fizzle.png");
    m_rectangles.push_back(Rectangle(600, 600, 200, 150));

    constexpr int StartX = 5, StartY = 125, incrementValue = 125;

    for (int i = 0; i < 3; i++) {
        m_textureNames.push_back(std::format("textures/btn{}.png", i));
        m_rectangles.push_back(Rectangle(StartX, StartY + (i * incrementValue), 200, 100));
    }

    m_buttonCallbacks.push_back([this](int) { m_game->GetSceneManager()->ChangeScene("Game"); });
    m_buttonCallbacks.push_back([this](int) { m_game->GetSceneManager()->ChangeScene("Options"); });
    m_buttonCallbacks.push_back([this](int) { m_game->Exit(); });
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

    auto mousePos = m_inputManager->GetMousePosition();
    Rectangle mouseRect(mousePos.GetX(), mousePos.GetY(), 1, 1);

    for (int i = 1; i < 4; i++) { // Start from index 1 to skip the first texture
        if (m_rectangles[i].intersects(mouseRect)) {
            if (m_inputManager->IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
                // Button is clicked, call the corresponding callback
                if (auto it = std::next(m_buttonCallbacks.begin(), i - 1); it != m_buttonCallbacks.end()) {
                    (*it)(i - 1);
                }
            }
        }
    }
}

void MenuScene::Draw() {
    m_game->GetSpriteBatch()->Begin();

    for (const auto &[textureName, rect]: std::views::zip(m_textureNames, m_rectangles)) {
        Color drawColor = (textureName == m_textureNames[0]) ? Color::White : m_textureColor; // Default color for non-button textures
        if (Texture const *texture = m_game->GetContentManager()->Get<Texture>(textureName)) {
            m_game->GetSpriteBatch()->Draw(*texture, rect, drawColor);
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