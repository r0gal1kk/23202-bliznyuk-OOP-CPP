#ifndef GAME_H
#define GAME_H

#include "Universe.h"
#include <string>

class Game {
private:
    bool gameActive;
    Universe universe;
public:
    explicit Game(const std::string& filename);
    void run();
};

#endif // GAME_H
