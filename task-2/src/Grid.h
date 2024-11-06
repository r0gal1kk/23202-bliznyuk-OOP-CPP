#ifndef GRID_H
#define GRID_H

#include <vector>
#include <iostream>

class Grid {
private:
    std::vector<std::vector<bool>> cells;
    int rows;
    int cols;
public:
    Grid();
    Grid(const int& rows, const int& cols);

    void setCell(const int& row, const int& col, const bool& value);
    bool getCell(const int& row, const int& col) const;
    int getRows() const;
    int getCols() const;
};

#endif // GRID_H
