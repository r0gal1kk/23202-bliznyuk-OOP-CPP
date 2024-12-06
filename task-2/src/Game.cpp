#include "Game.h"
#include "UniverseReader.h"

Game::Game(const std::string& filename) : universe(UniverseReader::loadFromFile(filename)), commandProcessor(universe) {}

void Game::run() {
    std::cout << "Press enter to start the game...";
    std::cin.get();
    Grid currentField = universe.getField();

    universe.display(currentField);
    std::cout << "Enter command: ";

    std::string command;
    while (commandProcessor.isGameActive()) {
        std::getline(std::cin, command);
        commandProcessor.processCommand(command, currentField);
        if (commandProcessor.isGameActive()) {
            std::cout << "Enter command: ";
        }
    }
}

void Game::runOffline(const std::string &outputName, const int &iterations) {
    Grid currentField = universe.getField();
    for (int i = 0; i < iterations; i++) {
        currentField = universe.update(currentField);
    }
    UniverseWriter::writeToFile(universe, currentField, outputName);
}
