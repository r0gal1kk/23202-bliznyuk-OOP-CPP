#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include <unordered_set>
#include <utility>
#include <sstream>

class Rule {
private:
    std::unordered_set<int> birthRules;
    std::unordered_set<int> survivalRules;
public:
    Rule(const std::string& birthRule, const std::string& survivalRule) {
        for (const auto c : birthRule) {
            if (isdigit(c)) {
                birthRules.insert(c - '0');
            }
        }
        for (const auto c : survivalRule) {
            if (isdigit(c)) {
                survivalRules.insert(c - '0');
            }
        }
    }

    bool shouldBorn(const int& liveNeighbours) const {
        return birthRules.count(liveNeighbours);
    }

    bool shouldSurvive(const int& liveNeighbours) const {
        return survivalRules.count(liveNeighbours);
    }
};

class Grid {
private:
    std::vector<std::vector<bool>> cells;
    int rows;
    int cols;
public:
    Grid() {
        rows = 35;
        cols = 35;
        cells = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    }

    Grid(const int& rows, const int& cols) {
        this->rows = rows;
        this->cols = cols;
        cells = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
    }

    void setCell(const int row, const int col, const bool value) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Invalid cell index" << std::endl;
        }
        cells[row][col] = value;
    }

    bool getCell(const int row, const int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Invalid cell index" << std::endl;
        }
        return cells[row][col];
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }
};

class Universe {
private:
    Grid field;
    unsigned long long generation;
    const int birthRule = 3;

    int countNeighbours(const Grid& currentField, const int row, const int col) {
        int count = 0;
        const int rows = currentField.getRows();
        const int cols = currentField.getCols();
        for (int rowShift = -1; rowShift <= 1; ++rowShift) {
            for (int colShift = -1; colShift <= 1; ++colShift) {
                if (rowShift == 0 && colShift == 0) {
                    continue;
                }
                const int rowNum = (row + rowShift + rows) % rows;
                const int colNum = (col + colShift + cols) % cols;
                if (currentField.getCell(rowNum, colNum)) {
                    count++;
                }
            }
        }
        return count;
    }

public:
    Universe() {
        generation = 1;
        field = Grid();
    }

    Universe(const int& rows, const int& cols) {
        generation = 1;
        field = Grid(rows, cols);
    }
    //рофлометод для проверки работы
    void initialize() {
        std::ifstream input("defaultUniverse.txt");
        while (!input.eof()) {
            int x, y;
            input >> x >> y;
            field.setCell(x, y, true);
        }
    }

    Grid getField() const {
        return field;
    }

    unsigned long long getGeneration() const {
        return generation;
    }

    Grid update(const Grid& currentField) {
        generation++;
        const int rows = currentField.getRows();
        const int cols = currentField.getCols();
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                const int neighbours = countNeighbours(currentField, row, col);
                const bool alive = currentField.getCell(row, col);
                if (!alive && neighbours == birthRule) {
                    field.setCell(row, col, true);
                }
                else if (alive && (neighbours < 2 || neighbours > birthRule)) {
                    field.setCell(row, col, false);
                }
                else {
                    field.setCell(row, col, alive);
                }
            }
        }
        return field;
    }

    void display(const Grid& currentField) {
        system("cls");
        std::cout << "Generation: " << generation << std::endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        const int rows = field.getRows();
        const int cols = field.getCols();
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (currentField.getCell(row, col)) {
                    SetConsoleTextAttribute(hConsole, 0 | (0 << 4));
                    std::cout << "  ";
                }
                else {
                    SetConsoleTextAttribute(hConsole, 15 | (15 << 4));
                    std::cout << "  ";
                }
            }
            SetConsoleTextAttribute(hConsole, 7 | (0 << 4));
            std::cout << std::endl;
        }
    }
    friend class UniverseLoader;
};

class UniverseLoader {
private:
    static void readName(const std::string& line, std::string& name, bool& hasName) {
        const std::string namePart = line.substr(3);
        if (namePart.empty()) {
            name = "MyUniverse";
            std::cerr << "Warning: No name provided. Using default name 'MyUniverse'.\nUsage: #N <name>" << std::endl;
        } else {
            name = namePart;
        }
        hasName = true;
    }

    static void readRules(const std::string& line, Rule& rule, bool& hasRule) {
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

    static void readDimensions(const std::string& line, int& width, int& height, bool& hasDimensions) {
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

    static void readCoords(const std::string& line, const int& width, const int& height, std::vector<std::pair<int, int>>& liveCells, const bool& hasDimensions, bool& hasCoords) {
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

    static void handleNonCriticalErrors(const bool& hasName, const bool& hasRule, const bool& hasDimensions, const std::vector<std::pair<int, int>>& liveCells, Rule& rule, int& width, int& height) {
        if (!hasName) {
            std::cerr << "Warning: No name found in the file. Using default name 'MyUniverse'.\n"
                         "Use #N <name> in the beginning of the file to set custom name." << std::endl;
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
public:
    static Universe loadFromFile(const std::string& filename, Rule& rule) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string line;
        std::string name;
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

        handleNonCriticalErrors(hasName, hasRule, hasDimensions, liveCells, rule, width, height);

        Universe universe(width, height);
        for (const auto& cell : liveCells) {
            universe.field.setCell(cell.first, cell.second, true);
        }

        return universe;
    }
};

class Game {
private:
    bool gameActive;
    Universe universe;
    std::string filename;
public:
    Game(std::string filename) {
        gameActive = false;
        this->filename = filename;
    }
    void run() {
        gameActive = true;
        universe.initialize();
        Grid currentField = universe.getField();
        while (gameActive) {
            universe.display(currentField);
            currentField = universe.update(currentField);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
};

int main(int argc, char* argv[]) {
    std::string filename = "defaultUniverse.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    Game game(filename);
    game.run();
    return 0;
}
