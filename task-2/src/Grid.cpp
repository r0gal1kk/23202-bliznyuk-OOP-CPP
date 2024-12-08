#include "Grid.h"

Grid::Grid() {
    rows = 0;
    cols = 0;
    cells = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
}

Grid::Grid(const int& rows, const int& cols) {
    this->rows = rows;
    this->cols = cols;
    cells = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
}

void Grid::setCell(const int& row, const int& col, const bool& value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cerr << "Invalid cell index" << std::endl;
    }
    cells[row][col] = value;
}

bool Grid::getCell(const int& row, const int& col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        std::cerr << "Invalid cell index" << std::endl;
    }
    return cells[row][col];
}

int Grid::getRows() const {
    return rows;
}

int Grid::getCols() const {
    return cols;
}
