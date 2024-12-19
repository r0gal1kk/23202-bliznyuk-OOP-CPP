#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "iostream"
#include "stdexcept"

enum class ErrorCode {
    INVALID_ARGUMENTS = 1,
    UNSUPPORTED_FORMAT = 2,
    CONFIG_PARSE_ERROR = 3,
    FILE_IO_ERROR = 4,
    CONVERSION_ERROR = 5,
    UNKNOWN_ERROR = 6
};

class SoundProcessorException : public std::runtime_error {
private:
    ErrorCode code;
public:
    explicit SoundProcessorException(const std::string& msg, ErrorCode code);
    ErrorCode getCode() const;
};

class InvalidArgumentsException : public SoundProcessorException {
public:
    explicit InvalidArgumentsException(const std::string& msg);
};

class UnsupportedFormatException : public SoundProcessorException {
public:
    explicit UnsupportedFormatException(const std::string& msg);
};

class ConfigParseException : public SoundProcessorException {
public:
    explicit ConfigParseException(const std::string& msg);
};

class FileIOException : public SoundProcessorException {
public:
    explicit FileIOException(const std::string& msg);
};

class ConversionException : public SoundProcessorException {
public:
    explicit ConversionException(const std::string& msg);
};
#endif
