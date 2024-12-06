#ifndef GAME_H
#define GAME_H

#include "Universe.h"
#include "CommandProcessor.h"
#include <string>

class Game {
private:
    Universe universe;
    CommandProcessor commandProcessor;

public:
    explicit Game(const std::string& filename);
    void run();
    void runOffline(const std::string& outputName, const int& iterations);
};

#endif // GAME_H
