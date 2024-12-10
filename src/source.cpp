#include <glad/glad.h>
#include <Game.h>
#include <iostream>
#include <mutex>
#include <Window.h>
#include <Renderer.h>
#include <thread>
#include <Color.h>

std::mutex mtx;

void renderLoop(Window *window, Renderer *renderer);

int main(int argc, char *argv[]) {
    try {
        Window window("FizzleFramework!", 1600, 900);
        Renderer renderer;
        Game game;

        std::thread renderThread(renderLoop, &window, &renderer);

        while (!window.ShouldClose()) {
            window.PollEvents();
            // Game logic update can go here
            game.Update();
        }

        renderThread.join();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void renderLoop(Window *window, Renderer *renderer) {
    while (!window->ShouldClose()) {
        {
            std::lock_guard lock(mtx);

            renderer->Clear();
            // Add your rendering code here

            window->SwapBuffers();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
