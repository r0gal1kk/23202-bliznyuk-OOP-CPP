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

void FileWriter::write(const std::string& str) {
    if (output.is_open()) {
        output.write(str.c_str(), str.length());
    }
}
