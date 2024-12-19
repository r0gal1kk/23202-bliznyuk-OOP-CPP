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

class Exceptions : public std::runtime_error {
private:
    ErrorCode code;
public:
    explicit Exceptions(const std::string& msg, ErrorCode code);
    ErrorCode getErrorType() const;
};

class InvalidArgumentsException : public Exceptions {
public:
    explicit InvalidArgumentsException(const std::string& msg);
};

class UnsupportedFormatException : public Exceptions {
public:
    explicit UnsupportedFormatException(const std::string& msg);
};

class ConfigParseException : public Exceptions {
public:
    explicit ConfigParseException(const std::string& msg);
};

class FileIOException : public Exceptions {
public:
    explicit FileIOException(const std::string& msg);
};

class ConversionException : public Exceptions {
public:
    explicit ConversionException(const std::string& msg);
};
#endif
