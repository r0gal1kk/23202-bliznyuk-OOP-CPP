#ifndef LAB3_MUTECONVERTER_H
#define LAB3_MUTECONVERTER_H

#include "Converter.h"

class MuteConverter : public Converter {
public:
    void apply(WAVFile& wavFile, const std::vector<std::string>& params) const override;
    std::string getDescription() const override;
};

#endif // LAB3_MUTECONVERTER_H
