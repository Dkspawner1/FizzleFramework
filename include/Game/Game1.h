#ifndef GAME1_H
#define GAME1_H
#include <Game.h>
#include <Window.h>
#include <Renderer.h>

class Game1 final : public Game {
public:
    Game1() : window("FizzleFramework!", 1600, 900), renderer() {
    }

protected:
    void Initialize() override;

    void LoadContent() override;

    void Update(GameTime &gameTime) override {
        window.PollEvents();
    }

    void Draw() override {
        renderer.Clear();
        window.SwapBuffers();
    }

private:
    Window window;
    Renderer renderer;
};

#endif //GAME1_H
