#include "WAVFileWriter.h"
#include <fstream>
#include <stdexcept>

WAVFileWriter::WAVFileWriter(const std::string &fileName) {
    this->filename = fileName;
}

WAVFileWriter::~WAVFileWriter() = default;

void WAVFileWriter::write(const WAVHeader& header, const std::vector<int16_t>& samples) {
    // Открытие файла для записи в бинарном режиме
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    // Запись заголовка
    file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));
    if (!file) {
        throw std::runtime_error("Failed to write WAV header");
    }

    // Запись аудиоданных
    file.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));
    if (!file) {
        throw std::runtime_error("Failed to write WAV samples");
    }

    // Закрытие файла
    file.close();
    if (!file) {
        throw std::runtime_error("Failed to close the file after writing: " + filename);
    }
}
