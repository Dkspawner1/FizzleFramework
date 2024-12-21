#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <list>
#include <Scenes/Scene.h>
#include <Game/Game1.h>
#include <vector>
#include <string>

class MenuScene final : public Scene {
public:
    explicit MenuScene(Game *game) : Scene(game) {
    }

    void Initialize() override;

    void LoadContent() override;

    void Update(GameTime &gameTime) override;

    void Draw() override;

    void UnloadContent() override;

private:
    std::unique_ptr<InputManager> m_inputManager;
    Color m_textureColor = Color::White;
    std::vector<std::string> m_textureNames;

    std::vector<Rectangle> m_rectangles;
    std::list<std::function<void(int)> > m_buttonCallbacks;
};

#endif // MENUSCENE_H
