#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <string>
#include <vector>

class ConfigParser {
public:
    explicit ConfigParser(const std::string& filename);
    ~ConfigParser();
    std::vector<std::string> parseLine(const int& lineIndex) const;
    size_t getLinesCount() const;
private:
    std::string filename;
    std::vector<std::string> lines;
};

#endif
