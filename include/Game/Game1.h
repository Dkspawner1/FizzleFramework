#ifndef GAME1_H
#define GAME1_H

#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <Content/Texture.h>
#include <Core/Game.h>
#include <Core/InputManager.h>
#include <Graphics/SpriteBatch.h>
#include <Scenes/SceneManager.h>
#include <Threading/JobSystem.h>

class Game1 final : public Game {
public:
    Game1() : m_sceneManager(std::make_unique<SceneManager>(this)), m_jobSystem(std::make_unique<JobSystem>()) {
    }

    ~Game1() override;

    void Run() override { Game::Run(); }
    SpriteBatch *GetSpriteBatch() const { return spriteBatch.get(); }
    Window *GetWindow() const { return graphics->GetWindow(); }
    SceneManager *GetSceneManager() const { return m_sceneManager.get(); }

protected:
    void Initialize() override;

    void LoadContent() override;

    void Update(GameTime &gameTime) override;

    void Draw() override;

private:
    // Managers
    std::unique_ptr<InputManager> m_inputManager;
    std::unique_ptr<SceneManager> m_sceneManager;
    // Content
    std::vector<std::unique_ptr<Texture> > m_textures;
    Color m_texColor = Color::White;
    Rectangle m_texRect{200, 400, 400, 200};
    // Multithreading
    std::unique_ptr<JobSystem> m_jobSystem;
    std::unique_ptr<SpriteBatch> spriteBatch; // SpriteBatch instance
};

#endif // GAME1_H
