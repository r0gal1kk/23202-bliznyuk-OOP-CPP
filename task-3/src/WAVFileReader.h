#ifndef WAVFILEREADER_H
#define WAVFILEREADER_H

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>

struct WAVHeader {
    char chunkID[4];
    uint32_t chunkSize;
    char format[4];
    char subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    char subchunk2ID[4];
    uint32_t subchunk2Size;
};

class WAVFileReader {
public:
    explicit WAVFileReader(const std::string &filename);
    ~WAVFileReader();
    const WAVHeader& getHeader() const;
    const std::vector<int16_t>& getSamples() const;
    void read();
private:
    std::string filename;
    WAVHeader header;
    std::vector<int16_t> samples;
};

#endif