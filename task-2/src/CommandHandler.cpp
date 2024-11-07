#include "CommandHandler.h"
#include <iostream>
#include <sstream>

CommandHandler::CommandHandler(Universe& universe) : universe(universe), gameActive(true) {}

void CommandHandler::handleDumpCommand(const std::vector<std::string>& args, const Grid& currentField) const {
    if (args.size() != 1) {
        std::cerr << "Usage: dump <filename>" << std::endl;
        return;
    }
    UniverseWriter::writeToFile(universe, currentField, args[0]);
    std::cout << "This universe has been saved to file " + args[0] << std::endl;
}

void CommandHandler::handleTickCommand(const std::vector<std::string>& args, Grid &currentField) const {
    int n = 1;
    if (args.size() == 1) {
        try {
            n = std::stoi(args[0]);
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid number of ticks. Using default value 1." << std::endl;
        }
    }
    for (int i = 0; i < n; ++i) {
        currentField = universe.update(currentField);
    }
    universe.display(currentField);
}

void CommandHandler::handleExitCommand() {
    gameActive = false;
    std::cout << "Bye!" << std::endl;
}

void CommandHandler::handleHelpCommand(const std::vector<std::string>& args) const {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  dump <filename> - Save the universe to a file" << std::endl;
    std::cout << "  tick <n=1> (or t <n=1>) - Calculate n iterations and print the result" << std::endl;
    std::cout << "  exit - Exit the game" << std::endl;
    std::cout << "  help - Print this help message" << std::endl;
}

void CommandHandler::processCommand(const std::string& command, Grid& currentField) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    if (cmd == "dump") {
        handleDumpCommand(args, currentField);
    } else if (cmd == "tick" || cmd == "t") {
        handleTickCommand(args, currentField);
    } else if (cmd == "exit") {
        handleExitCommand();
    } else if (cmd == "help") {
        handleHelpCommand(args);
    } else {
        std::cerr << "Unknown command: " << cmd << std::endl << "Use help to see available commands" << std::endl;
    }
}

bool CommandHandler::isGameActive() const {
    return gameActive;
}
