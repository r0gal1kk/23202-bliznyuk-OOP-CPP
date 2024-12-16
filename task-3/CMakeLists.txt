cmake_minimum_required(VERSION 3.29)
project(task_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_3 main.cpp
        src/ConfigParser.cpp
        src/ConfigParser.h
        src/SoundProcessor.cpp
        src/SoundProcessor.h
        src/WAVFile.cpp
        src/WAVFile.h
        src/Converter.cpp
        src/Converter.h
        src/MuteConverter.cpp
        src/MuteConverter.h
        src/MixConverter.cpp
        src/MixConverter.h
        src/FastConverter.cpp
        src/FastConverter.h
        src/ConverterFactory.cpp
        src/ConverterFactory.h
        src/CommandLineParser.cpp
        src/CommandLineParser.h
        src/Exceptions.cpp
        src/Exceptions.h)
