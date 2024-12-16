#ifndef LAB3_CONVERTER_H
#define LAB3_CONVERTER_H

#include "WAVFile.h"
#include <vector>
#include <string>

class Converter {
public:
    virtual ~Converter() = default;
    virtual void apply(WAVFile& wavFile, const std::vector<std::string>& params) const = 0;
    virtual std::string getDescription() const = 0;
};

#endif // LAB3_CONVERTER_H
