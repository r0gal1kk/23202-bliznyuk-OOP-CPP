#ifndef DUMPHANDLER_H
#define DUMPHANDLER_H

#include "CommandHandler.h"
#include "UniverseWriter.h"
#include <iostream>

class DumpHandler : public CommandHandler {
public:
    void handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const override;
};

#endif // DUMPHANDLER_H
