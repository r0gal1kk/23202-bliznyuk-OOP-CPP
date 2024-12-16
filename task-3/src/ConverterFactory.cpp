#include "ConverterFactory.h"

#include "FastConverter.h"
#include "MixConverter.h"
#include "MuteConverter.h"
#include "regex"

ConverterFactory::ConverterFactory() {
    converters["mute"] = new MuteConverter(0, 0);
    converters["mix"] = new MixConverter(1, 0);
    converters["fast"] = new FastConverter(0, 0, 0);
}

ConverterFactory::~ConverterFactory() {
    for (const auto& converter : converters) {
        delete converter.second;
    }
    converters.clear();
}

