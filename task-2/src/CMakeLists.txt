set(SOURCES
        Game.cpp
        CommandHandler.cpp
        Grid.cpp
        Rule.cpp
        Universe.cpp
        UniverseReader.cpp
        UniverseWriter.cpp)

set(HEADERS
        Game.h
        CommandHandler.h
        Grid.h
        Rule.h
        Universe.h
        UniverseReader.h
        UniverseWriter.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})