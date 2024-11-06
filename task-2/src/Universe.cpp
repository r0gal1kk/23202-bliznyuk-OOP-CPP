#include "Universe.h"
#include <fstream>
#include <iostream>

Universe::Universe() {
    generation = 1;
    field = Grid();
}

Universe::Universe(const int& rows, const int& cols, const std::string& name, const Rule& rule) {
    generation = 1;
    field = Grid(rows, cols);
    this->name = name;
    this->rule = rule;
}

void Universe::initialize() {
    std::ifstream input("defaultUniverse.txt");
    while (!input.eof()) {
        int x, y;
        input >> x >> y;
        field.setCell(x, y, true);
    }
}

Grid Universe::getField() const {
    return field;
}

unsigned long long Universe::getGeneration() const {
    return generation;
}

int Universe::countNeighbours(const Grid& currentField, const int row, const int col) {
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

Grid Universe::update(const Grid& currentField) {
    generation++;
    const int rows = currentField.getRows();
    const int cols = currentField.getCols();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            const int neighbours = countNeighbours(currentField, row, col);
            const bool alive = currentField.getCell(row, col);
            if (!alive && rule.shouldBorn(neighbours)) {
                field.setCell(row, col, true);
            }
            else if (alive && !rule.shouldSurvive(neighbours)) {
                field.setCell(row, col, false);
            }
            else {
                field.setCell(row, col, alive);
            }
        }
    }
    return field;
}

void Universe::display(const Grid& currentField) {
    system("cls");
    std::cout << name << std::endl;
    std::cout << "Height: " << currentField.getRows() << std::endl;
    std::cout << "Width: " << currentField.getCols() << std::endl;
    std::cout << "Generation: " << generation << std::endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    const int rows = field.getRows();
    const int cols = field.getCols();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (currentField.getCell(row, col)) {
                SetConsoleTextAttribute(hConsole, 0 | (0 << 4));
            }
            else {
                SetConsoleTextAttribute(hConsole, 15 | (15 << 4));
            }
            std::cout << "  ";
        }
        SetConsoleTextAttribute(hConsole, 7 | (0 << 4));
        std::cout << std::endl;
    }
}
