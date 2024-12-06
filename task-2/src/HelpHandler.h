#ifndef HELPHANDLER_H
#define HELPHANDLER_H

#include "CommandHandler.h"
#include <iostream>

class HelpHandler : public CommandHandler {
public:
    void handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const override;
};

#endif // HELPHANDLER_H
