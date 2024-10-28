#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <fstream>
#include <string>
#include <vector>
#include <utility>

class FileWriter {
private:
    std::string fileName;
    std::ofstream output;
public:
    FileWriter(std::string fileName);
    ~FileWriter();
    void open();
    void close();
    void write(const std::vector<std::string> &stats);
};

#endif //FILEWRITER_H
