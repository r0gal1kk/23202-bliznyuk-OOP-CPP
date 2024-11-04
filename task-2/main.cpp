#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <Windows.h>

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
};

class Game {
private:
    bool gameActive;
    Universe universe;
public:
    Game() {
        gameActive = false;
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

int main() {
    Game game;
    game.run();
    return 0;
}
