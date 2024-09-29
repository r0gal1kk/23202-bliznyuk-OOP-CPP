#include "FileWriter.h"

FileWriter::FileWriter(std::string fileName) : fileName(fileName) {}

FileWriter::~FileWriter() {
    if (output.is_open()) {
        close();
    }
}

void FileWriter::open() {
    output.open(fileName);
}

void FileWriter::close() {
    if (output.is_open()) {
        output.close();
    }
}

void FileWriter::writeStatisticToCSV(const std::vector<std::pair<std::string, int>>& statisticVector, const unsigned long long& wordsTotal) {
    if (output.is_open()) {
        for (const auto& element : statisticVector) {
            double frequency = static_cast<double>(element.second) / wordsTotal * 100;
            output << element.first << '\t' << element.second << '\t' << frequency << '%' << '\n';
        }
    }
}
