#include <Scenes/LoadingScene.h>
#include <iostream>


void LoadingScene::Initialize() {
    m_font= "tf.fnt";
}

void LoadingScene::LoadContent() {
        try {
            m_game->GetContentManager()->ClaimAsset<SpriteFont>(m_font);
            std::cout << "Font " << m_font << " loaded successfully" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Failed to load font " << m_font << ": " << e.what() << std::endl;
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

    m_game->GetSpriteBatch()->End();
}

void LoadingScene::UnloadContent() {
    // Unload any content specific to this scene if necessary
}

void LoadingScene::SetProgress(float progress) {
    m_progress = progress; // Set the current progress
}
