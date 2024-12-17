#include <Scenes/LoadingScene.h>
#include <iostream>

#include "Graphics/Font.h"


void LoadingScene::Initialize() {
    m_font = m_game->GetContentManager()->ClaimAsset<Font>("arial.ttf");
}

void LoadingScene::LoadContent() {

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

    std::cout << "Loading... " << static_cast<int>(m_progress * 100) << "%\n";

    // Draw progress bar (example)
    float barWidth = 400;
    float filledWidth = barWidth * m_progress;

    std::cout << "[" << std::string(static_cast<int>(filledWidth / 4), '=')
            << std::string(static_cast<int>((barWidth - filledWidth) / 4), ' ')
            << "]\n";

    m_game->GetSpriteBatch()->DrawString(*m_font, "Hello, World asdfhasdiu fhauisd fhiuh21iu wh I!uih siurh !", 100, 100, 1.0f, Color::Black);

    m_game->GetSpriteBatch()->End();
}

void LoadingScene::UnloadContent() {
}

void LoadingScene::SetProgress(float progress) {
    m_progress = progress; // Set the current progress
}
