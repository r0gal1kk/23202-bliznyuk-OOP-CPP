#include "UniverseWriter.h"
#include <fstream>

void UniverseWriter::writeToFile(const Universe& universe, const Grid& currentField, const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Failed to open file " + filename);
    }
    outfile << "#N " << universe.name << std::endl;
    outfile << universe.rule.getRuleString() << std::endl;
    outfile << "#S " << currentField.getRows() << " " << currentField.getCols() << std::endl;
    for (int row = 0; row < currentField.getRows(); row++) {
        for (int col = 0; col < currentField.getCols(); col++) {
            if (currentField.getCell(row, col)) {
                outfile << row << " " << col << std::endl;
            }
        }
    }
    outfile.close();
}
