#include "SoundProcessor.h"
#include <stdexcept>

#include "WAVFileWriter.h"

SoundProcessor::SoundProcessor(const std::string &configFile, const std::vector<std::string> &inputFiles, const std::string &outputFile) {
    this->configFile = configFile;
    this->inputFiles = inputFiles;
    this->outputFile = outputFile;
    inputSamples.resize(inputFiles.size());
}

void SoundProcessor::createConverters() {
    const ConfigParser parser(configFile);
    for (int i = 0; i < parser.getLinesCount(); i++) {
        std::vector<std::string> args = parser.parseLine(i);
        if (args.empty() || args[0].front() == '#') {
            continue;
        }
        Converter* converter = nullptr;
        if (args[0] == "mute") {
            MuteFactory muteFactory;
            converter = muteFactory.create(args);
        } else if (args[0] == "mix") {
            MixFactory mixFactory;
            converter = mixFactory.create(args);
        } else if (args[0] == "fast") {
            FastFactory fastFactory;
            converter = fastFactory.create(args);
        } else {
            throw std::invalid_argument("Unknown converter type: " + args[0]);
        }
        if (converter) {
            converters.push_back(converter);
        }
    }
}

void SoundProcessor::readInputFiles() {
    for (int i = 0; i < inputFiles.size(); i++) {
        WAVFileReader reader(inputFiles[i]);
        reader.read();
        inputSamples[i] = reader.getSamples();
    }
}

void SoundProcessor::process() {
    WAVFileReader reader(inputFiles[0]);
    reader.read();
    std::vector<int16_t> resultSamples = reader.getSamples();
    readInputFiles();
    createConverters();
    for (const auto &converter : converters) {
        resultSamples = converter->convert(resultSamples, inputSamples);
        delete converter;
    }
    WAVFileWriter writer(outputFile);
    WAVHeader header = reader.getHeader();
    header.subchunk2Size = resultSamples.size() * sizeof(int16_t);
    writer.write(header, resultSamples);
}
