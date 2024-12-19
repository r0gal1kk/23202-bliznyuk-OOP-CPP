#ifndef SOUNDPROCESSOR_H
#define SOUNDPROCESSOR_H

#include <string>
#include <vector>
#include "ConfigParser.h"
#include "WAVFileReader.h"
#include "ConverterFactory.h"

class SoundProcessor {
public:
    SoundProcessor(const std::string& configFile,
                   const std::vector<std::string>& inputFiles,
                   const std::string& outputFile);

    ~SoundProcessor();
    void process();

private:
    std::string configFile;
    std::vector<std::string> inputFiles;
    std::string outputFile;
    std::vector<Converter*> converters;
    std::vector<std::vector<int16_t>> inputSamples;
    void createConverters();
    void readInputFiles();
};

#endif
