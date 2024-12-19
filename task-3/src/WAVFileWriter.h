#ifndef WAVFILEWRITER_H
#define WAVFILEWRITER_H
#include <string>
#include "WAVFileReader.h"

class WAVFileWriter {
public:
    explicit WAVFileWriter(const std::string& fileName);
    ~WAVFileWriter();
    void write(const WAVHeader& header, const std::vector<int16_t>& samples);
private:
    std::string filename;
};

#endif //WAVFILEWRITER_H
