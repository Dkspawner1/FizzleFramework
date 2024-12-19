#include <Scenes/LoadingScene.h>
#include <iostream>

#include "Graphics/Font.h"


void LoadingScene::Initialize() {
    m_font = m_game->GetContentManager()->ClaimAsset<Font>("Fonts/DMSans-Variable.ttf");
}

void LoadingScene::LoadContent() {
}

void LoadingScene::Update(GameTime &gameTime) {
    if (m_progress < 1.0f) {
        m_progress += 0.0025f;
        if (m_progress >= 1.0f) {
            m_finished = true;
        }
    }
    if (m_finished)
        m_game->GetSceneManager()->ChangeScene("Menu"); // Switch to Game scene when done
}


void LoadingScene::DrawLoadingBar() const {
    if (!m_game || !m_game->GetGraphicsDeviceManager() || !m_game->GetSpriteBatch()) {
        return;  // Early exit if any pointer is null
    }

    const auto &graphicsDevice = m_game->GetGraphicsDeviceManager();
    const auto &spriteBatch = m_game->GetSpriteBatch();

    int windowWidth = graphicsDevice->GetWindow()->GetWidth();
    int windowHeight = graphicsDevice->GetWindow()->GetHeight();
    float centerX = windowWidth / 2.0f;
    float centerY = windowHeight / 2.0f;

    const float barWidth = 400.0f;
    const float barHeight = 30.0f;
    const float padding = 20.0f;

    float barX = centerX - (barWidth / 2.0f);
    float barY = centerY - (barHeight / 2.0f);

    // Draw background (gray)
    Rectangle barBg(barX, barY, barWidth, barHeight);
    spriteBatch->Draw(barBg, Color(200, 200, 200));

    // Draw progress fill (white)
    float fillWidth = barWidth * m_progress;
    Rectangle barFill(barX, barY, fillWidth, barHeight);
    spriteBatch->Draw(barFill, Color::White);

    // Format and draw percentage text
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << (m_progress * 100) << "%";
    spriteBatch->DrawString(*m_font, ss.str(), barX, barY - padding, 1.0f, Color::Black);
}

void LoadingScene::Draw() {
    if (!m_game || !m_game->GetSpriteBatch()) {
        return;  // Early exit if game or spriteBatch is null
    }

    m_game->GetSpriteBatch()->Begin();
    DrawLoadingBar();
    m_game->GetSpriteBatch()->End();
}


void LoadingScene::UnloadContent() {
    if (m_game && m_game->GetContentManager()) {
        m_game->GetContentManager()->ReleaseAsset("Fonts/DMSans-Variable.ttf");
    }
}

void LoadingScene::SetProgress(float progress) {
    m_progress = progress;
}
