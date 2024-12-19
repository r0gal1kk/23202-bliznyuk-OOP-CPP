#include "WAVFileReader.h"
#include <fstream>
#include <cstring>

WAVFileReader::WAVFileReader(const std::string &filename) {
    this->filename = filename;
}

WAVFileReader::~WAVFileReader() = default;

const WAVHeader &WAVFileReader::getHeader() const {
    return header;
}

const std::vector<int16_t>& WAVFileReader::getSamples() const {
    return samples;
}

void WAVFileReader::read() {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
     //   throw FileNotFoundException("Cannot open WAV file: " + filename);
    }
    file.read(reinterpret_cast<char *>(&header.chunkID), 4);
    file.read(reinterpret_cast<char *>(&header.chunkSize), 4);
    file.read(reinterpret_cast<char *>(&header.format), 4);
    if (std::strncmp(header.chunkID, "RIFF", 4) != 0 ||
        std::strncmp(header.format, "WAVE", 4) != 0) {
     //   throw InvalidFormatException("Invalid WAV file format: " + filename);
    }
    file.read(reinterpret_cast<char *>(&header.subchunk1ID), 4);
    file.read(reinterpret_cast<char *>(&header.subchunk1Size), 4);
    file.read(reinterpret_cast<char *>(&header.audioFormat), 2);
    if(header.audioFormat != 1) {
    //    throw InvalidFormatException("Must be no compress: " + filename);
    }
    file.read(reinterpret_cast<char *>(&header.numChannels), 2);
    if (header.numChannels != 1) {
    //    throw InvalidFormatException("Must be mono: " + filename);
    }
    file.read(reinterpret_cast<char *>(&header.sampleRate), 4);
    if (header.sampleRate != 44100) {
    //    throw InvalidFormatException("Must be 44100 hz: " + filename);
    }
    file.read(reinterpret_cast<char *>(&header.byteRate), 4);
    file.read(reinterpret_cast<char *>(&header.blockAlign), 2);
    file.read(reinterpret_cast<char *>(&header.bitsPerSample), 2);
    if(header.bitsPerSample != 16) {
    //    throw InvalidFormatException("Must be 16 bits per sample: " + filename);
    }
    if (std::strncmp(header.subchunk1ID, "fmt ", 4) != 0 || header.audioFormat
        != 1) {
    //    throw InvalidFormatException("Unsupported WAV format: " + filename);
    }
    uint32_t subchunkSize;
    while (true) {
        char subchunkID[4];
        file.read(subchunkID, 4);
        file.read(reinterpret_cast<char *>(&subchunkSize), 4);
        if (std::strncmp(subchunkID, "data", 4) == 0) {
            header.subchunk2ID[0] = subchunkID[0];
            header.subchunk2ID[1] = subchunkID[1];
            header.subchunk2ID[2] = subchunkID[2];
            header.subchunk2ID[3] = subchunkID[3];
            header.subchunk2Size = subchunkSize;
            break;
        }
        file.seekg(subchunkSize, std::ios::cur);
    }
    const int numSamples = header.subchunk2Size / (header.bitsPerSample / 8);
    samples.resize(numSamples);
    file.read(reinterpret_cast<char *>(samples.data()), header.subchunk2Size);
    if (!file) {
    //    throw FileNotFoundException(
    //            "Failed to read WAV data from file: " + filename);
    }
}
