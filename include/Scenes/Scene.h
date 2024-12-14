#ifndef SCENE_H
#define SCENE_H
#include <Core/GameTime.h>
#include <Core/Game.h>


class Scene {
public:
    explicit Scene(Game* game);

    virtual ~Scene() = default;

    virtual void Initialize() = 0;

    virtual void LoadContent() = 0;

    virtual void Update(GameTime &gameTime) = 0;

    virtual void Draw() = 0;

    virtual void UnloadContent() = 0;

protected:
    Game* m_game;
};

#endif //SCENE_H
