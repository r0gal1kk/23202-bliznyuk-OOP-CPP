#include "CommandProcessor.h"
#include "ExitHandler.h"
#include "DumpHandler.h"
#include "TickHandler.h"
#include "HelpHandler.h"
#include <sstream>

CommandProcessor::CommandProcessor(Universe& universe) : universe(universe) {
    handlerMap["exit"] = new ExitHandler();
    handlerMap["dump"] = new DumpHandler();
    handlerMap["tick"] = new TickHandler();
    handlerMap["t"] = handlerMap["tick"];
    handlerMap["help"] = new HelpHandler();
}

CommandProcessor::~CommandProcessor() {
    for (const auto& pair : handlerMap) {
        delete pair.second;
    }
    handlerMap.clear();
}

void CommandProcessor::processCommand(const std::string& commandLine, Grid& currentField) {
    std::istringstream iss(commandLine);
    std::string command;
    iss >> command;

    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }

    const auto it = handlerMap.find(command);
    if (it != handlerMap.end()) {
        it->second->handle(args, universe, currentField, gameActive);
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}

bool CommandProcessor::isGameActive() const {
    return gameActive;
}
