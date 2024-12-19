#ifndef CONVERTER_H
#define CONVERTER_H

#include "WAVFileReader.h"
#include <vector>
#include <string>

class Converter {
public:
    virtual ~Converter() = default;
    virtual std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                        const std::vector<std::vector<int16_t>> &extraInputs) const = 0;
    //virtual std::string getDescription() const = 0;
protected:
    const int sampleRate = 44100;
};

class MuteConverter : public Converter {
public:
    explicit MuteConverter(const std::vector<std::string>& parameters);
    std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                const std::vector<std::vector<int16_t>> &extraInputs) const override;
    //std::string getDescription() const override;
private:
    int start;
    int end;
};

class MixConverter : public Converter {
public:
    explicit MixConverter(const std::vector<std::string>& parameters);
    std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                const std::vector<std::vector<int16_t>> &extraInputs) const override;
    //std::string getDescription() const override;
private:
    int fileNumber;
    int start;
};

class FastConverter : public Converter {
public:
    explicit FastConverter(const std::vector<std::string>& parameters);
    std::vector<int16_t> convert(const std::vector<int16_t> &samples,
                                const std::vector<std::vector<int16_t>> &extraInputs) const override;
    //std::string getDescription() const override;
private:
    int start;
    int end;
    int coefficient;
};

#endif
