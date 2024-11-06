#include "src/Game.h"

int main(int argc, char* argv[]) {
    std::string filename = "defaultUniverse.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    Game game(filename);
    game.run();
    return 0;
}
