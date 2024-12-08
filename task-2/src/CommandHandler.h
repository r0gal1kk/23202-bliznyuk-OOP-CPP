#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>
#include <vector>
#include "Universe.h"
#include "UniverseWriter.h"

class CommandHandler {
public:
    virtual ~CommandHandler() = default;
    virtual void handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const = 0;
};

#endif // COMMANDHANDLER_H
