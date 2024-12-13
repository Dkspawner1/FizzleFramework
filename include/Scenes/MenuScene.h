#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <Scenes/Scene.h>
#include <Game/Game1.h>

class MenuScene final : public Scene {
public:
    explicit MenuScene(Game1* game);

    void Initialize() override;
    void LoadContent() override;
    void Update(GameTime& gameTime) override;
    void Draw() override;
    void UnloadContent() override;

private:
    Game1* m_game; // Reference to the main game
    std::unique_ptr<InputManager> m_inputManager; // Input manager
    std::vector<std::unique_ptr<Texture>> m_textures; // Textures for this scene
    Color m_texColor = Color::White; // Current texture color
    Rectangle m_texRect{200, 400, 400, 200}; // Rectangle for texture positioning
};

#endif // MENUSCENE_H
