#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <string>


class ConfigReader {
private:
    std::string fileName;
public:
    explicit ConfigReader(std::string fileName);
};



#endif //CONFIGREADER_H
