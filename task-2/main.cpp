#include "Game.h"

int main(int argc, char* argv[]) {
    std::string inputName = "defaultUniverse.txt";
    if (argc == 2) {
        inputName = argv[1];
    }
    else if (argc == 4 || argc == 6) {
        inputName = argv[1];
        std::string outputName;
        int iterations = 0;
        for (int i = 2; i < argc; i++) {
            std::string arg = argv[i];
            if (arg == "-i" || arg.substr(0, 13) == "--iterations=") {
                if (arg == "-i") {
                    iterations = std::stoi(argv[++i]);
                }
                else {
                    iterations = std::stoi(arg.substr(13));
                }
            }
            else if (arg == "-o" || arg.substr(0, 9) == "--output=") {
                if (arg == "-o") {
                    outputName = argv[++i];
                }
                else {
                    outputName = arg.substr(9);
                }
            }
            else {
                std::cerr << "Invalid argument: " << arg << std::endl;
                std::cerr << "Usage: <input file> --iterations=<n> --output=<output file>" << std::endl;
                std::cerr << "or <input file> -i <n> -o <output file>" << std::endl;
                return 1;
            }
        }
        if (iterations < 0 || inputName.empty() || outputName.empty()) {
            std::cerr << "Invalid arguments" << std::endl;
            std::cerr << "Usage: <input file> --iterations=<n> --output=<output file>" << std::endl;
            std::cerr << "or <input file> -i <n> -o <output file>" << std::endl;
        }
        Game game(inputName);
        game.runOffline(outputName, iterations);
        return 0;
    }
    Game game(inputName);
    game.run();
    return 0;
}
