#include "ConfigParser.h"
#include <sstream>
#include <fstream>

#include "Exceptions.h"

ConfigParser::ConfigParser(const std::string &filename) {
    this->filename = filename;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw FileIOException("ConfigParser: Could not open config file");
    }
    std::string line;
    while (std::getline(file, line)) {
        this->lines.push_back(line);
    }
    file.close();
}

ConfigParser::~ConfigParser() = default;

std::vector<std::string> ConfigParser::parseLine(const int& lineIndex) const {
    std::istringstream iss(lines[lineIndex]);
    std::vector<std::string> args;
    std::string arg;
    while (iss >> arg) {
        args.push_back(arg);
    }
    return args;
}

size_t ConfigParser::getLinesCount() const {
    return lines.size();
}
