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

void FileWriter::write(const std::vector<std::string> &stats) {
    for (auto element : stats) {
        output << element;
    }
}
