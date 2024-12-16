cmake_minimum_required(VERSION 3.29)
project(task_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_3 main.cpp
        src/ConfigReader.cpp
        src/ConfigReader.h)
