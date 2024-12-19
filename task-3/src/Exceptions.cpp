#include "Exceptions.h"

Exceptions:: Exceptions(const std::string& msg, ErrorCode code)
: std::runtime_error(msg), code(code) {}

ErrorCode Exceptions:: getErrorType() const {
    return code;
}

InvalidArgumentsException:: InvalidArgumentsException(const std::string& msg)
: Exceptions(msg, ErrorCode::INVALID_ARGUMENTS) {}

UnsupportedFormatException:: UnsupportedFormatException(const std::string& msg)
: Exceptions(msg, ErrorCode::UNSUPPORTED_FORMAT) {}

ConfigParseException::ConfigParseException(const std::string& msg)
: Exceptions(msg, ErrorCode::CONFIG_PARSE_ERROR) {}

FileIOException::FileIOException(const std::string& msg)
: Exceptions(msg, ErrorCode::FILE_IO_ERROR) {}

ConversionException::ConversionException(const std::string& msg)
: Exceptions(msg, ErrorCode::CONVERSION_ERROR) {}
