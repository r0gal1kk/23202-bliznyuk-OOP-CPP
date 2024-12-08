#ifndef EXITHANDLER_H
#define EXITHANDLER_H

#include "CommandHandler.h"
#include <iostream>

class ExitHandler : public CommandHandler {
public:
    void handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const override;
};

#endif // EXITHANDLER_H