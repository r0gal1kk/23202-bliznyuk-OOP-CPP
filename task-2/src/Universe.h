#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Grid.h"
#include "Rule.h"
#include <string>
#include <Windows.h>

class Universe {
private:
    Grid field;
    unsigned long long generation;
    Rule rule;
    std::string name;

    int countNeighbours(const Grid& currentField, const int row, const int col);

public:
    Universe();
    Universe(const int& rows, const int& cols, const std::string& name, const Rule& rule);

    void initialize();
    Grid getField() const;
    unsigned long long getGeneration() const;
    Grid update(const Grid& currentField);
    void display(const Grid& currentField);

    friend class UniverseLoader;
};

#endif // UNIVERSE_H
