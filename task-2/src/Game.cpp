#include "Game.h"
#include "UniverseReader.h"

Game::Game(const std::string& filename) : universe(UniverseReader::loadFromFile(filename)), commandHandler(universe) {}

void Game::run() {
    std::cout << "Press enter to start the game...";
    std::cin.get();
    Grid currentField = universe.getField();

    universe.display(currentField);
    std::cout << "Enter command: ";

    std::string command;
    while (commandHandler.isGameActive()) {
        std::getline(std::cin, command);
        commandHandler.processCommand(command, currentField);
        if (commandHandler.isGameActive()) {
            std::cout << "Enter command: ";
        }
    }
}
