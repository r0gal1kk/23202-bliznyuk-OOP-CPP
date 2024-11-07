#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
#include <vector>
#include "Universe.h"
#include "UniverseWriter.h"

class CommandHandler {
private:
    Universe& universe;
    bool gameActive;

    void handleDumpCommand(const std::vector<std::string>& args, const Grid &currentField) const;
    void handleTickCommand(const std::vector<std::string>& args, Grid &currentField) const;
    void handleExitCommand();
    void handleHelpCommand(const std::vector<std::string>& args) const;

public:
    explicit CommandHandler(Universe& universe);
    void processCommand(const std::string& command, Grid& currentField);
    bool isGameActive() const;
};

#endif // COMMANDHANDLER_H
