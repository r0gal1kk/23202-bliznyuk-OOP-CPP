set(SOURCES
        BitArray.cpp)

set(HEADERS
        BitArray.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})