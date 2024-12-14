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
    Game1() : m_jobSystem(std::make_unique<JobSystem>()) {
        m_sceneManager = std::make_unique<SceneManager>(this);
    }

    ~Game1() override = default;

    Window *GetWindow() const { return GetGraphicsDeviceManager()->GetWindow(); }

    friend int main(int argc, char *argv[]);

protected:
    void Initialize() override;

    void LoadContent() override;

    void Update(GameTime &gameTime) override;

    void Draw() override;
    std::unique_ptr<SceneManager> m_sceneManager;


private:
    std::unique_ptr<InputManager> m_inputManager;
    std::unique_ptr<JobSystem> m_jobSystem;
};

#endif // GAME1_H
