#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <Scenes/Scene.h>
#include <Game/Game1.h>

class GameScene : public Scene {
public:
    explicit GameScene(Game1 *game); // Constructor declaration

    void Initialize() override;
    void LoadContent() override;
    void Update(GameTime &gameTime) override;
    void Draw() override;
    void UnloadContent() override;

private:
    Game1 *m_game; // Reference to the main game
};

#endif // GAMESCENE_H
