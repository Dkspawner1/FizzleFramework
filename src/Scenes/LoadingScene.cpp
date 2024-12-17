#include <Scenes/LoadingScene.h>
#include <iostream>


void LoadingScene::Initialize() {
    m_fonts.push_back("tf.fnt");
}

void LoadingScene::LoadContent() {
    for (const auto &font: m_fonts) {
        try {
            // m_game->GetContentManager()->ClaimAsset<SpriteFont>(font);
            std::cout << "Font " << font << " loaded successfully" << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Failed to load font " << font << ": " << e.what() << std::endl;
        }
    }
}

void LoadingScene::Update(GameTime &gameTime) {
    // Here you would typically check if content is loaded and update progress
    // For demonstration, let's increment progress
    if (m_progress < 1.0f) {
        m_progress += 0.01f; // Increment progress (replace with actual loading logic)
        if (m_progress >= 1.0f) {
            m_finished = true;
        }
    }
    if (m_finished)
        m_game->GetSceneManager()->ChangeScene("Menu"); // Switch to Game scene when done
}

void LoadingScene::Draw() {
    m_game->GetSpriteBatch()->Begin();

    // Draw loading text
    std::cout << "Loading... " << static_cast<int>(m_progress * 100) << "%\n";

    // Draw progress bar (example)
    float barWidth = 400; // Width of the progress bar
    float filledWidth = barWidth * m_progress; // Width of filled part based on progress

    // Draw filled part of the bar (you would replace this with actual drawing code)
    std::cout << "[" << std::string(static_cast<int>(filledWidth / 4), '=')
            << std::string(static_cast<int>((barWidth - filledWidth) / 4), ' ')
            << "]\n";
    // if (SpriteFont const *font = m_game->GetContentManager()->Get<SpriteFont>(m_fonts[0])) {
    //     // font->DrawString("This is a test!", 100.0f, 100.0f, Color::Black);
    //     m_game->GetSpriteBatch()->DrawString(*font, "THIS IS A TEST!!!", 100, 100, Color::Black);
    // }
    m_game->GetSpriteBatch()->End();
}

void LoadingScene::UnloadContent() {
    // Unload any content specific to this scene if necessary
}

void LoadingScene::SetProgress(float progress) {
    m_progress = progress; // Set the current progress
}
