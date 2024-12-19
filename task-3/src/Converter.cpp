#include "Converter.h"
#include <regex>
#include "Exceptions.h"

MuteConverter::MuteConverter(const std::vector<std::string>& parameters) {
    if (parameters.size() != 3) {
        throw InvalidArgumentsException("Mute Converter requires exactly 3 arguments: mute <start> <end>");
    }
    const std::regex numberRegex(R"(\d+)");
    if (!std::regex_match(parameters[1], numberRegex) || !std::regex_match(parameters[2], numberRegex)) {
        throw InvalidArgumentsException("Mute Converter: start and end must be positive integers");
    }
    start = std::stoi(parameters[1]);
    end = std::stoi(parameters[2]);
    if (start >= end) {
        throw InvalidArgumentsException("Mute Converter: start time must be less than end time");
    }
}

MixConverter::MixConverter(const std::vector<std::string>& parameters) {
    if (parameters.size() != 3) {
        throw InvalidArgumentsException("Mix Converter requires exactly 3 arguments: mix <fileNumber> <start>");
    }
    const std::regex fileRegex(R"(\$\d+)");
    const std::regex numberRegex(R"(\d+)");
    if (!std::regex_match(parameters[1], fileRegex)) {
        throw InvalidArgumentsException("Mix Converter: fileNumber must be in the format $<number>");
    }
    if (!std::regex_match(parameters[2], numberRegex)) {
        throw InvalidArgumentsException("Mix Converter: start must be a positive integer");
    }
    fileNumber = std::stoi(parameters[1].substr(1));
    start = std::stoi(parameters[2]);
}

FastConverter::FastConverter(const std::vector<std::string>& parameters) {
    if (parameters.size() != 4) {
        throw InvalidArgumentsException("Fast Converter requires exactly 4 arguments: fast <start> <end> <coefficient>");
    }
    const std::regex numberRegex(R"(\d+)");
    if (!std::regex_match(parameters[1], numberRegex) ||
        !std::regex_match(parameters[2], numberRegex) ||
        !std::regex_match(parameters[3], numberRegex)) {
        throw InvalidArgumentsException("Fast Converter: start, end, and coefficient must be positive integers");
    }
    start = std::stoi(parameters[1]);
    end = std::stoi(parameters[2]);
    coefficient = std::stoi(parameters[3]);
    if (start >= end) {
        throw InvalidArgumentsException("Fast Converter: Invalid time range");
    }
}

std::vector<int16_t> MuteConverter::convert(const std::vector<int16_t> &samples, const std::vector<std::vector<int16_t>> &extraInputs) const {
    std::vector<int16_t> result = samples;
    const int startMute = start * sampleRate;
    const int endMute = end * sampleRate;
    for (int i = startMute; i < endMute; i++) {
        result[i] = 0;
    }
    return result;
}

std::vector<int16_t> MixConverter::convert(const std::vector<int16_t> &samples, const std::vector<std::vector<int16_t>> &extraInputs) const {
    std::vector<int16_t> result = samples;
    const std::vector<int16_t>& secondStream = extraInputs[fileNumber - 1];
    const int startMix = start * sampleRate;
    const int minSize = std::min(result.size() - startMix, secondStream.size());
    for (int i = 0; i < minSize; i++) {
        result[startMix + i] = (result[startMix + i] + secondStream[i]) / 2;
    }
    return result;
}

std::vector<int16_t> FastConverter::convert(const std::vector<int16_t> &samples, const std::vector<std::vector<int16_t>> &extraInputs) const {
    const int startAcceleration = start * sampleRate;
    const int endAcceleration = end * sampleRate;
    const std::vector<int16_t> fragment(samples.begin() + startAcceleration, samples.begin() + endAcceleration);
    std::vector<int16_t> acceleratedFragment;
    acceleratedFragment.reserve((fragment.size() + coefficient - 1) / coefficient);
    for (size_t i = 0; i < fragment.size(); i += coefficient) {
        acceleratedFragment.push_back(fragment[i]);
    }
    std::vector<int16_t> result;
    result.reserve(samples.size() - fragment.size() + acceleratedFragment.size());
    // До фрагмента
    result.insert(result.end(), samples.begin(), samples.begin() + startAcceleration);
    // Ускоренный фрагмент
    result.insert(result.end(), acceleratedFragment.begin(), acceleratedFragment.end());
    // После фрагмента
    result.insert(result.end(), samples.begin() + endAcceleration, samples.end());
    return result;
}

std::string MuteConverter::getDescription() const {
    return "Mutes audio fragment of input1.wav\n"
           "Usage: mute <start second> <end second>\n\n";
}

std::string MixConverter::getDescription() const {
    return "Mixes audio fragment of input1.wav with other input.wav\n"
           "Usage: mix $<input file number> <start second>\n\n";
}

std::string FastConverter::getDescription() const {
    return "Accelerates audio fragment of input1.wav by integer multiplier\n"
           "Usage: fast <start> <end> <acceleration coefficient>\n\n";
}