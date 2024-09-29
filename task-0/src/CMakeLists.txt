set(SOURCES
        Statistic.cpp FileReader.cpp FileWriter.cpp Parser.cpp)

set(HEADERS
        Statistic.h FileReader.h FileWriter.h Parser.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})