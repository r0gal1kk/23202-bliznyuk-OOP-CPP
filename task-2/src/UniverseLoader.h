#ifndef UNIVERSELOADER_H
#define UNIVERSELOADER_H

#include "Universe.h"
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <stdexcept>

class UniverseLoader {
private:
    static void readName(const std::string& line, std::string& name, bool& hasName);
    static void readRules(const std::string& line, Rule& rule, bool& hasRule);
    static void readDimensions(const std::string& line, int& width, int& height, bool& hasDimensions);
    static void readCoords(const std::string& line, const int& width, const int& height, std::vector<std::pair<int, int>>& liveCells, const bool& hasDimensions, bool& hasCoords);
    static void handleNonCriticalErrors(const bool& hasName, const bool& hasRule, const bool& hasDimensions, const std::vector<std::pair<int, int>>& liveCells, Rule& rule, int& width, int& height, std::string& name);

public:
    static Universe loadFromFile(const std::string& filename);
};

#endif // UNIVERSELOADER_H
