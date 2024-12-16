#ifndef LAB3_SOUNDPROCESSOR_H
#define LAB3_SOUNDPROCESSOR_H

#include <string>
#include <vector>
#include "ConfigParser.h"
#include "WAVFile.h"
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

    void validateInputs() const;
    void processConversions(WAVFile& currentFile, const std::vector<Converter*>& converters);
};

#endif // LAB3_SOUNDPROCESSOR_H
