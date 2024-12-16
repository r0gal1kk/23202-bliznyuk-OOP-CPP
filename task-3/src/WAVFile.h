#ifndef LAB3_WAVFILE_H
#define LAB3_WAVFILE_H

#include <string>
#include <vector>
#include <cstdint>
#include "Exceptions.h"

class WAVFile {
public:
    explicit WAVFile(const std::string& filename);
    WAVFile(uint32_t sampleRate, uint16_t bitsPerSample, uint16_t numChannels);

    void save(const std::string& filename) const;

    const std::vector<int16_t>& getSamples() const;
    void setSamples(const std::vector<int16_t>& newSamples);

    uint32_t getSampleRate() const;
    uint16_t getBitsPerSample() const;
    uint16_t getNumChannels() const;

private:
    struct WAVHeader {
        char riff[4];
        uint32_t chunkSize;
        char wave[4];
        char fmt[4];
        uint32_t subchunk1Size;
        uint16_t audioFormat;
        uint16_t numChannels;
        uint32_t sampleRate;
        uint32_t byteRate;
        uint16_t blockAlign;
        uint16_t bitsPerSample;
        char data[4];
        uint32_t subchunk2Size;
    } header;

    std::vector<int16_t> samples;

    void readFile(const std::string& filename);
    void writeFile(const std::string& filename) const;
    void validateHeader() const;
};

#endif // LAB3_WAVFILE_H
