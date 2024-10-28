#include "FileReader.h"

FileReader::FileReader(std::string fileName) : fileName(fileName) {}

FileReader::~FileReader() {
    if (input.is_open()) {
        close();
    }
}

void FileReader::open() {
    input.open(fileName);
}

void FileReader::close() {
    if (input.is_open()) {
        input.close();
    }
}

bool FileReader::hasNext() {
    if (input.peek() == EOF) {
        return false;
    }
    return !input.eof();
}

std::string FileReader::getNextString() {
    std::string buffer;
    getline(input, buffer);
    return buffer;
}
