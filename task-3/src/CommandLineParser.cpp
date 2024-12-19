#include "CommandLineParser.h"
#include <iostream>
#include <stdexcept>
#include <regex>

void CommandLineParser::printHelp() const {
    std::cout << "Usage:\n"
              << "sound_processor [-h] [-c config.txt output.wav input1.wav [input2.wav …]]\n\n"
              << "Parameters:\n"
              << "-h : show this help\n"
              << "-c config.txt output.wav input1.wav [input2.wav ...] : run processing\n\n";
}

bool CommandLineParser::checkFormat(const std::string &arg, const std::string &format) {
    const std::regex wavRegex(R"((.*)\.wav)", std::regex_constants::icase);
    const std::regex txtRegex(R"((.*)\.txt)", std::regex_constants::icase);
    if (format == ".txt") {
        return std::regex_match(arg, txtRegex);
    }
    return std::regex_match(arg, wavRegex);
}

void CommandLineParser::parse() {
    if (argc < 2) {
        throw std::invalid_argument("Wrong number of arguments");
    }
    std::string arg = argv[1];
    if (arg == "-h") {
        printHelp();
    }
    else if (arg == "-c" && argc > 2) {
        arg = argv[2];
        if (checkFormat(arg, ".txt")) {
            configFile = arg;
        }
        else {
            throw std::invalid_argument("Second argument is not a valid .txt file");
        }
        arg = argv[3];
        if (checkFormat(arg, ".wav")) {
            outputFile = arg;
        }
        else {
            throw std::invalid_argument("Third argument is not a valid .wav file");
        }
        for (int i = 4; i < argc; i++) {
            arg = argv[i];
            if (checkFormat(arg, ".wav")) {
                inputFiles.push_back(arg);
            }
            else {
                throw std::invalid_argument("Input argument is not a valid .wav file");
            }
        }
    }
}

CommandLineParser::CommandLineParser(int argc, char **argv) : argc(argc), argv(argv), showHelp(false) {
    parse();
}

std::string CommandLineParser::getConfigFile() const {
    return configFile;
}

std::string CommandLineParser::getOutputFile() const {
    return outputFile;
}

std::vector<std::string> CommandLineParser::getInputFiles() const {
    return inputFiles;
}
