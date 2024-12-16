#ifndef LAB3_FASTCONVERTER_H
#define LAB3_FASTCONVERTER_H

#include "Converter.h"

class FastConverter : public Converter {
public:
    void apply(WAVFile& wavFile, const std::vector<std::string>& params) const override;
    std::string getDescription() const override;
};

#endif // LAB3_FASTCONVERTER_H
