#ifndef TICKHANDLER_H
#define TICKHANDLER_H

#include "CommandHandler.h"
#include <iostream>

class TickHandler : public CommandHandler {
public:
    void handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const override;
};

#endif // TICKHANDLER_H