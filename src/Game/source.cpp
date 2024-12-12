#include <glad/glad.h>
#include <Core/Game.h>
#include <iostream>

std::mutex mtx;


int main(int argc, char *argv[]) {
    try {
        Game game;
        game.Run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
