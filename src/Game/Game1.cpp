#include <Game/Game1.h>
#include <Core/Rectangle.h>
#include <Graphics/Color.h>

void Game1::Initialize() {
    Game::Initialize();
    // Add any Game1-specific initialization here
}

void Game1::LoadContent() {
    // Load game-specific content here
}

void Game1::Update(GameTime &gameTime) {
    // Add game-specific update logic here
}

void Game1::Draw() {
    spriteBatch->Begin();
    // Add game-specific drawing code here
    Rectangle rect(100, 100, 200, 200);
    Color color(1.0f, 0.0f, 0.0f, 1.0f);
    spriteBatch->Draw(rect, color);
    spriteBatch->End();
}
