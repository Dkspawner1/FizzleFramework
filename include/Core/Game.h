#ifndef GAME_H
#define GAME_H

#include <memory>
#include <Content/ContentManager.h>
#include <Core/GameTime.h>
#include <Graphics/GraphicsDeviceManager.h>
#include <Graphics/SpriteBatch.h>

class Game {
public:
    Game();
    virtual ~Game();
    void Run();

protected:
    virtual void Initialize();
    virtual void LoadContent();
    virtual void Update(GameTime &gameTime);
    virtual void Draw();

    std::unique_ptr<GraphicsDeviceManager> graphics;
    std::unique_ptr<ContentManager> content;
    std::unique_ptr<SpriteBatch> spriteBatch;
    GameTime gameTime;
};

#endif //GAME_H
