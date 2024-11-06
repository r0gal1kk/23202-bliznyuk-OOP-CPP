#include "Game.h"
#include "UniverseLoader.h"
#include <thread>
#include <chrono>

Game::Game(const std::string& filename) {
    gameActive = false;
    universe = UniverseLoader::loadFromFile(filename);
}

void Game::run() {
    gameActive = true;
    Grid currentField = universe.getField();
    while (gameActive) {
        universe.display(currentField);
        currentField = universe.update(currentField);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
