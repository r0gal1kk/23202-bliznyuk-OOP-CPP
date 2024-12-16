#ifndef LAB3_CONVERTERFACTORY_H
#define LAB3_CONVERTERFACTORY_H

#include <string>
#include <unordered_map>
#include "Converter.h"

class ConverterFactory {
public:
    ConverterFactory();
    ~ConverterFactory();
    Converter* createConverter(const std::string& line) const;

private:
    std::unordered_map<std::string, Converter*> converters;
};

#endif // LAB3_CONVERTERFACTORY_H
