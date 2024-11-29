#include "gtest/gtest.h"
#include "Game.h"
#include <UniverseReader.h>
#include <fstream>

void createInputFile(const std::string& fileName) {
    std::ofstream tempFile(fileName);
    tempFile << "#N Glider\n";
    tempFile << "#R B3/S23\n";
    tempFile << "#S 10 10\n";
    tempFile << "0 1\n";
    tempFile << "1 2\n";
    tempFile << "2 0\n";
    tempFile << "2 1\n";
    tempFile << "2 2\n";
    tempFile.close();
}

TEST (GameTest, InitialState) {
    createInputFile("input.txt");
    const Universe universe = UniverseReader::loadFromFile("input.txt");
    const Grid field = universe.getField();
    EXPECT_TRUE(field.getCell(0, 1));
    EXPECT_TRUE(field.getCell(1, 2));
    EXPECT_TRUE(field.getCell(2, 0));
    EXPECT_TRUE(field.getCell(2, 1));
    EXPECT_TRUE(field.getCell(2, 2));
    EXPECT_FALSE(field.getCell(0, 0));
    EXPECT_FALSE(field.getCell(1, 1));
    std::remove("input.txt");
}

TEST (GameTest, Tick) {
    createInputFile("input.txt");
    Universe universe = UniverseReader::loadFromFile("input.txt");
    Grid field = universe.getField();
    CommandHandler handler(universe);
    handler.processCommand("t 1", field);
    EXPECT_TRUE(field.getCell(1, 0));
    EXPECT_TRUE(field.getCell(1, 2));
    EXPECT_TRUE(field.getCell(2, 1));
    EXPECT_TRUE(field.getCell(2, 2));
    EXPECT_TRUE(field.getCell(3, 1));
    EXPECT_FALSE(field.getCell(0, 1));
    EXPECT_FALSE(field.getCell(2, 0));
    std::remove("input.txt");
}

TEST (GameTest, Dump) {
    createInputFile("input.txt");
    Universe universe = UniverseReader::loadFromFile("input.txt");
    Grid field = universe.getField();
    CommandHandler handler(universe);
    handler.processCommand("dump output.txt", field);
    std::ifstream tempFile("output.txt");
    std::string line;
    std::getline(tempFile, line);
    EXPECT_EQ(line, "#N Glider");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "#R B3/S23");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "#S 10 10");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "0 1");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "1 2");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "2 0");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "2 1");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "2 2");
    std::remove("input.txt");
    std::remove("output.txt");
}

TEST (GameTest, OfflineMode) {
    createInputFile("input.txt");
    Game game("input.txt");
    game.runOffline("output.txt", 100);
    std::ifstream tempFile("output.txt");
    std::string line;
    std::getline(tempFile, line);
    EXPECT_EQ(line, "#N Glider");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "#R B3/S23");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "#S 10 10");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "5 6");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "6 7");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "7 5");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "7 6");
    std::getline(tempFile, line);
    EXPECT_EQ(line, "7 7");
    std::remove("input.txt");
    std::remove("output.txt");
}
