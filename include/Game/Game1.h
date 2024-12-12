#ifndef GAME1_H
#define GAME1_H

#include <Core/Game.h>

class Game1 final : public Game {
protected:
    void Initialize() override;
    void LoadContent() override;
    void Update(GameTime &gameTime) override;
    void Draw() override;
};

#endif //GAME1_H
