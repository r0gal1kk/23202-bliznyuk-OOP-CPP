cmake_minimum_required(VERSION 3.29)
project(task_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_2 main.cpp
        src/Rule.h
        src/Rule.cpp
        src/Grid.h
        src/Grid.cpp
        src/Universe.h
        src/Universe.cpp
        src/UniverseReader.h
        src/UniverseReader.cpp
        src/Game.h
        src/Game.cpp
        src/CommandHandler.h
        src/CommandHandler.cpp
        src/UniverseWriter.h
        src/UniverseWriter.cpp)
