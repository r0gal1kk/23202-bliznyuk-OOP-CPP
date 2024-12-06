#include "TickHandler.h"

void TickHandler::handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const {
    int n = 1;
    if (args.size() == 1) {
        try {
            n = std::stoi(args[0]);
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid number of ticks. Using default value 1." << std::endl;
        }
    }
    for (int i = 0; i < n; ++i) {
        currentField = universe.update(currentField);
    }
    universe.display(currentField);
}
