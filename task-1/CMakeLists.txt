cmake_minimum_required(VERSION 3.29)
project(task_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(task_1_run main.cpp)
# set this flag when running coverage tests in Clion
# set(CMAKE_CXX_FLAGS "--coverage")

# generate debug information
#set(CMAKE_CXX_FLAGS "-g")

include_directories(src)
add_subdirectory(src)

add_subdirectory(Google_tests)

target_link_libraries(${CMAKE_PROJECT_NAME}_run ${CMAKE_PROJECT_NAME}_lib)