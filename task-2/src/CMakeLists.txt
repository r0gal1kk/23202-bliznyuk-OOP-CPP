set(SOURCES
        Game.cpp
        Grid.cpp
        Rule.cpp
        Universe.cpp
        UniverseReader.cpp
        UniverseWriter.cpp
        HelpHandler.cpp
        ExitHandler.cpp
        DumpHandler.cpp
        TickHandler.cpp
        CommandProcessor.cpp)

set(HEADERS
        Game.h
        CommandHandler.h
        Grid.h
        Rule.h
        Universe.h
        UniverseReader.h
        UniverseWriter.h
        HelpHandler.cpp
        HelpHandler.h
        ExitHandler.h
        DumpHandler.h
        TickHandler.h
        CommandProcessor.h)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCES} ${HEADERS})