cmake_minimum_required(VERSION 3.29)
project(task_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(${CMAKE_PROJECT_NAME}_run main.cpp)

include_directories(src)
add_subdirectory(src)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)