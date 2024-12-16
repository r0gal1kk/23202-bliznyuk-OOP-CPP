#ifndef LAB3_MIXCONVERTER_H
#define LAB3_MIXCONVERTER_H

#include "Converter.h"

class MixConverter : public Converter {
public:
    void apply(WAVFile& wavFile, const std::vector<std::string>& params) const override;
    std::string getDescription() const override;
};

#endif // LAB3_MIXCONVERTER_H
