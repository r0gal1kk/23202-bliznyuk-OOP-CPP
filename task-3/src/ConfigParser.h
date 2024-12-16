#ifndef LAB3_CONFIGPARSER_H
#define LAB3_CONFIGPARSER_H

#include <string>
#include <vector>
#include "ConverterFactory.h"

class ConfigParser {
public:
    ConfigParser(const std::string& filename, const ConverterFactory& factory);
    ~ConfigParser();

    std::vector<Converter*> parse() const;

private:
    std::vector<std::string> lines;
    const ConverterFactory& factory;
};

#endif // LAB3_CONFIGPARSER_H
