#include "Exceptions.h"

SoundProcessorException:: SoundProcessorException(const std::string& msg, ErrorCode code)
: std::runtime_error(msg), code(code) {}

ErrorCode SoundProcessorException:: getCode() const {
    return code;
}

InvalidArgumentsException:: InvalidArgumentsException(const std::string& msg)
: SoundProcessorException(msg, ErrorCode::INVALID_ARGUMENTS) {}

UnsupportedFormatException:: UnsupportedFormatException(const std::string& msg)
: SoundProcessorException(msg, ErrorCode::UNSUPPORTED_FORMAT) {}

ConfigParseException::ConfigParseException(const std::string& msg)
: SoundProcessorException(msg, ErrorCode::CONFIG_PARSE_ERROR) {}

FileIOException::FileIOException(const std::string& msg)
: SoundProcessorException(msg, ErrorCode::FILE_IO_ERROR) {}

ConversionException::ConversionException(const std::string& msg)
: SoundProcessorException(msg, ErrorCode::CONVERSION_ERROR) {}
