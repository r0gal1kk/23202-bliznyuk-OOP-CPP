#include "ConverterFactory.h"

Converter *MuteFactory::create(std::vector<std::string> &args) const {
    return new MuteConverter(args);
}

Converter *MixFactory::create(std::vector<std::string> &args) const {
    return new MixConverter(args);
}

Converter *FastFactory::create(std::vector<std::string> &args) const {
    return new FastConverter(args);
}
