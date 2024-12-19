#ifndef CONVERTERFACTORY_H
#define CONVERTERFACTORY_H

#include <string>
#include "Converter.h"

class ConverterFactory {
public:
    virtual ~ConverterFactory() = default;
    virtual Converter* create(std::vector<std::string> &args) const = 0;
};

class MuteFactory : public ConverterFactory {
public:
    Converter* create(std::vector<std::string> &args) const override;
};

class MixFactory : public ConverterFactory {
public:
    Converter* create(std::vector<std::string> &args) const override;
};

class FastFactory : public ConverterFactory {
public:
    Converter* create(std::vector<std::string> &args) const override;
};

#endif // LAB3_CONVERTERFACTORY_H
