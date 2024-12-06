#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <unordered_map>
#include <string>
#include <memory>
#include "CommandHandler.h"
#include "Universe.h"
#include "Grid.h"

class CommandProcessor {
private:
    std::unordered_map<std::string, CommandHandler*> handlerMap;
    bool gameActive = true;
    Universe& universe;

public:
    explicit CommandProcessor(Universe& universe);
    ~CommandProcessor();
    void processCommand(const std::string& commandLine, Grid& currentField);
    bool isGameActive() const;
};

#endif // COMMANDPROCESSOR_H
