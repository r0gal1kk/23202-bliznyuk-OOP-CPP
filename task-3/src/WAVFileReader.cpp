#include "WAVFileReader.h"
#include <fstream>

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
        throw std::runtime_error("Could not open WAV file: " + filename);
    }
    // Чтение заголовка WAV
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));
    if (!file) {
        throw std::runtime_error("Failed to read WAV header");
    }

    // Проверка идентификаторов
    if (std::string(header.chunkID, 4) != "RIFF" || std::string(header.format, 4) != "WAVE") {
        throw std::runtime_error("Invalid WAV file format");
    }
    if (std::string(header.subchunk1ID, 4) != "fmt ") {
        throw std::runtime_error("Invalid WAV subchunk1 ID");
    }
    if (header.audioFormat != 1) { // 1 означает PCM
        throw std::runtime_error("Unsupported audio format (only PCM is supported)");
    }

    // Проверка параметров
    if (header.numChannels != 1) {
        throw std::runtime_error("Unsupported number of channels (only mono is supported)");
    }
    if (header.sampleRate != 44100) {
        throw std::runtime_error("Unsupported sample rate (only 44100 Hz is supported)");
    }
    if (header.bitsPerSample != 16) {
        throw std::runtime_error("Unsupported bit depth (only 16 bits per sample is supported)");
    }

    // Проверка subchunk2ID
    if (std::string(header.subchunk2ID, 4) != "data") {
        throw std::runtime_error("Invalid WAV subchunk2 ID");
    }

    // Проверка размера данных
    uint32_t dataSize = header.subchunk2Size;
    if (dataSize % sizeof(int16_t) != 0) {
        throw std::runtime_error("Data size is not aligned to 16-bit samples");
    }

    // Проверка корректности размера файла
    file.seekg(0, std::ios::end);
    const std::streampos fileSize = file.tellg();
    if (fileSize < sizeof(WAVHeader) + dataSize) {
        throw std::runtime_error("Invalid WAV file: data size mismatch");
    }

    // Переход к началу данных
    file.seekg(sizeof(WAVHeader), std::ios::beg);

    // Чтение данных
    const size_t numSamples = dataSize / sizeof(int16_t);
    samples.resize(numSamples);
    file.read(reinterpret_cast<char*>(samples.data()), dataSize);
    if (!file) {
        throw std::runtime_error("Failed to read WAV samples");
    }
    file.close();
}
