#ifndef GAME1_H
#define GAME1_H

#include <Core/Game.h>

#include "Content/Texture.h"
#include "Core/InputManager.h"

class Game1 final : public Game {
public:
    Game1() = default;

    void Run() override { Game::Run(); }

protected:
    void Initialize() override;

    void LoadContent() override;

    void Update(GameTime &gameTime) override;

    void Draw() override;

private:
    std::unique_ptr<InputManager> m_inputManager;
    std::vector<std::unique_ptr<Texture>> m_textures;
};

#endif //GAME1_H
