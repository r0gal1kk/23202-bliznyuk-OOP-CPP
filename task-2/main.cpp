#include "Game.h"

void printError(const std::string& arg) {
    std::cerr << "Invalid argument: " << arg << std::endl;
    std::cerr << "Usage: <input file> --iterations=<n> --output=<output file>" << std::endl;
    std::cerr << "or <input file> -i <n> -o <output file>" << std::endl;
}

bool parseArguments(int argc, char* argv[], std::string& inputFile, std::string& outputFile, int& iterations) {
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
                outputFile = argv[++i];
            }
            else {
                outputFile = arg.substr(9);
            }
        }
        else {
            printError(arg);
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    std::string inputName = "defaultUniverse.txt";
    if (argc == 2) {
        inputName = argv[1];
    }
    else if (argc == 4 || argc == 6) {
        inputName = argv[1];
        std::string outputName;
        int iterations = 0;
        const bool success = parseArguments(argc, argv, inputName, outputName, iterations);
        if (!success) {
            return 1;
        }
        if (iterations < 0 || inputName.empty() || outputName.empty()) {
            printError("negative iterations number or file name is empty.");
            return 1;
        }
        Game game(inputName);
        game.runOffline(outputName, iterations);
        return 0;
    }
    else if (argc != 1) {
        std::cerr << "Invalid number of arguments." << std::endl;
        return 1;
    }
    Game game(inputName);
    game.run();
    return 0;
}
