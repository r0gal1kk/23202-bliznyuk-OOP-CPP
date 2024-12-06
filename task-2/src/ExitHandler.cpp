#include "ExitHandler.h"

void ExitHandler::handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const {
    gameActive = false;
    std::cout << "Bye!" << std::endl;
}
