#include "DumpHandler.h"

void DumpHandler::handle(const std::vector<std::string>& args, Universe& universe, Grid& currentField, bool& gameActive) const {
    if (args.size() != 1) {
        std::cerr << "Usage: dump <filename>" << std::endl;
        return;
    }
    UniverseWriter::writeToFile(universe, currentField, args[0]);
    std::cout << "This universe has been saved to file " + args[0] << std::endl;
}