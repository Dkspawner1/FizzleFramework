#ifndef GAME_H
#define GAME_H

#include <memory>
#include <Content/ContentManager.h>
#include <Core/GameTime.h>
#include <Graphics/GraphicsDeviceManager.h>
#include <Graphics/SpriteBatch.h>

class SceneManager; // Forward declaration

class Game {
public:
    ContentManager *GetContentManager() const { return m_contentManager.get(); }
    GraphicsDeviceManager *GetGraphicsDeviceManager() const { return m_graphics.get(); }
    SpriteBatch *GetSpriteBatch() const { return m_spriteBatch.get(); }
    SceneManager *GetSceneManager() const { return m_sceneManager.get(); }

    void Exit();

protected:
    Game();

    virtual ~Game();

    virtual void Run();

    virtual void Initialize();

    virtual void LoadContent();

    virtual void Update(GameTime &gameTime);

    virtual void Draw();

    std::unique_ptr<SceneManager> m_sceneManager;

private:
    std::unique_ptr<GraphicsDeviceManager> m_graphics;
    std::unique_ptr<ContentManager> m_contentManager;
    std::unique_ptr<SpriteBatch> m_spriteBatch;
    GameTime m_gameTime;
};

#endif // GAME_H
