#ifndef UNIVERSEWRITER_H
#define UNIVERSEWRITER_H

#include "Universe.h"
#include <string>

class UniverseWriter {
public:
    static void writeToFile(const Universe &universe, const Grid &currentField, const std::string& filename);
};

#endif // UNIVERSEWRITER_H