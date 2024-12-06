#include "HelpHandler.h"

void HelpHandler::handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const {
    std::cout << "Available commands:" << std::endl;
    std::cout << "  dump <filename> - Save the universe to a file" << std::endl;
    std::cout << "  tick <n=1> (or t <n=1>) - Calculate n iterations and print the result" << std::endl;
    std::cout << "  exit - Exit the game" << std::endl;
    std::cout << "  help - Print this help message" << std::endl;
}
