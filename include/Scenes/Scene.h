#ifndef SCENE_H
#define SCENE_H
#include <Core/GameTime.h>

class Scene {
public:
    virtual ~Scene() = default;

    virtual void Initialize() = 0;
    virtual void LoadContent() = 0;
    virtual void Update(GameTime &gameTime) = 0;
    virtual void Draw() = 0;
    virtual void UnloadContent() = 0;
};

#endif //SCENE_H
