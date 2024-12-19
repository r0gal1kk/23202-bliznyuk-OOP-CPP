set(SOURCES
        CommandLineParser.cpp
        Converter.cpp
        ConfigParser.cpp
        ConverterFactory.cpp
        Exceptions.cpp
        SoundProcessor.cpp
        WAVFileReader.cpp
        WAVFileWriter.cpp)

set(HEADERS
    CommandLineParser.h
    ConfigParser.h
    Converter.h
    ConverterFactory.h
    Exceptions.h
    SoundProcessor.h
    WAVFileReader.h
    WAVFileWriter.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})