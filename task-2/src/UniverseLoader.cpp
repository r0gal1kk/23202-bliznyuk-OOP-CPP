#include "UniverseLoader.h"

void UniverseLoader::readName(const std::string& line, std::string& name, bool& hasName) {
    const std::string namePart = line.substr(3);
    if (namePart.empty()) {
        name = "MyUniverse";
        std::cerr << "Warning: No name provided. Using default name 'My Universe'.\nUsage: #N <name>" << std::endl;
    } else {
        name = namePart;
    }
    hasName = true;
}

void UniverseLoader::readRules(const std::string& line, Rule& rule, bool& hasRule) {
    std::string ruleStr = line.substr(3);
    const size_t pos = ruleStr.find('/');
    if (pos == std::string::npos) {
        std::cerr << "Warning: Invalid rule string format. Using default rule B3/S23.\n"
                     "Usage: #R B<birth rules>/S<survival rules>" << std::endl;
        rule = Rule("B3", "S23");
    } else {
        const std::string birthRule = ruleStr.substr(0, pos);
        const std::string survivalRule = ruleStr.substr(pos + 1);
        rule = Rule(birthRule, survivalRule);
    }
    hasRule = true;
}

void UniverseLoader::readDimensions(const std::string& line, int& width, int& height, bool& hasDimensions) {
    std::istringstream iss(line.substr(3));
    hasDimensions = true;
    int w = 0, h = 0;
    if (!(iss >> w)) {
        std::cerr << "Warning: Invalid size string format.\nUsage: #S <rows> <cols>" << std::endl;
        hasDimensions = false;
        return;
    }
    if (!(iss >> h)) {
        std::cerr << "Warning: Invalid size string format.\nUsage: #S <rows> <cols>" << std::endl;
        hasDimensions = false;
        return;
    }
    width = w;
    height = h;
}

void UniverseLoader::readCoords(const std::string& line, const int& width, const int& height, std::vector<std::pair<int, int>>& liveCells, const bool& hasDimensions, bool& hasCoords) {
    std::istringstream iss(line);
    int x, y;
    if (!(iss >> x >> y)) {
        std::cerr << "Warning: Invalid coordinate format. Skipping line: " << line << std::endl;
        return;
    }
    if (x < 0 || (x >= width && hasDimensions) || y < 0 || (y >= height && hasDimensions)) {
        std::cerr << "Warning: Coordinate (" << x << ", " << y << ") is out of bounds. Skipping line: " << line << std::endl;
        return;
    }
    //обход всего вектора ради warning
    for (const auto& cell : liveCells) {
        if (cell.first == x && cell.second == y) {
            std::cerr << "Warning: Duplicate coordinates (" << x << ", " << y << ") found in the file." << std::endl;
            return;
        }
    }
    const std::pair<int, int> coords = {x, y};
    liveCells.push_back(coords);
    hasCoords = true;
}

void UniverseLoader::handleNonCriticalErrors(const bool& hasName, const bool& hasRule, const bool& hasDimensions, const std::vector<std::pair<int, int>>& liveCells, Rule& rule, int& width, int& height, std::string& name) {
    if (!hasName) {
        std::cerr << "Warning: No name found in the file. Using default name 'My Universe'.\n"
                     "Use #N <name> in the beginning of the file to set custom name." << std::endl;
        name = "My Universe";
    }
    if (!hasRule) {
        std::cerr << "Warning: No rule found in the file. Using default rule B3/S23.\n"
                     "Use #R B<birth rules>/S<survival rules> in the beginning of the file to set custom rules" << std::endl;
        rule = Rule("B3", "S23");
    }
    if (!hasDimensions) {
        std::cerr << "Warning: No dimensions found in the file. Calculating minimum required dimensions.\n"
                     "Use #S <rows> <cols> in the beginning of the file to set custom dimensions" << std::endl;
        int maxX = 0, maxY = 0;
        for (const auto& cell : liveCells) {
            if (cell.first > maxX) maxX = cell.first;
            if (cell.second > maxY) maxY = cell.second;
        }
        width = maxX + 1;
        height = maxY + 1;
    }
}

Universe UniverseLoader::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    std::string name;
    Rule rule;
    int width = 0, height = 0;
    std::vector<std::pair<int, int>> liveCells;
    bool hasName = false;
    bool hasRule = false;
    bool hasDimensions = false;
    bool hasCoords = false;

    while (std::getline(file, line)) {
        if ((line.empty() || line[0] == '#') && !hasCoords) {
            if (line.find("#N ") == 0 && !hasName) {
                readName(line, name, hasName);
            } else if (line.find("#R ") == 0 && !hasRule) {
                readRules(line, rule, hasRule);
            } else if (line.find("#S ") == 0 && !hasDimensions) {
                readDimensions(line, width, height, hasDimensions);
            }
        } else {
            readCoords(line, width, height, liveCells, hasDimensions, hasCoords);
        }
    }

    file.close();

    handleNonCriticalErrors(hasName, hasRule, hasDimensions, liveCells, rule, width, height, name);

    Universe universe(width, height, name, rule);
    for (const auto& cell : liveCells) {
        universe.field.setCell(cell.first, cell.second, true);
    }

    return universe;
}
