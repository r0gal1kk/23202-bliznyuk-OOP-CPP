#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {
private:
    std::string fileName;
    std::ifstream input;
public:
    FileReader(std::string fileName);
    ~FileReader();
    void open();
    void close();
    bool hasNext();
    std::string getNextString();
};

#endif //FILEREADER_H
