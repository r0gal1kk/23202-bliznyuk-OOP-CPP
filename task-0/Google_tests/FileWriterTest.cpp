#include "FileWriter.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string>

TEST(FileWriterTest, TestWriteToFile) {
    std::string testFileName = "test_output.txt";

    // Удаляем файл, если он существует
    remove(testFileName.c_str());

    FileWriter fileWriter(testFileName);
    fileWriter.open();

    std::vector<std::pair<std::string, int>> statisticVector = {
        {"word1", 2},
        {"word2", 3}
    };

    unsigned long long wordsTotal = 5;
    fileWriter.writeStatisticToCSV(statisticVector, wordsTotal);
    fileWriter.close();

    // Проверяем, что файл был создан и содержит ожидаемые данные
    std::ifstream inFile(testFileName);
    ASSERT_TRUE(inFile.is_open());

    std::string line;
    std::getline(inFile, line);
    EXPECT_EQ(line, "word1\t2\t40%");

    std::getline(inFile, line);
    EXPECT_EQ(line, "word2\t3\t60%");

    inFile.close();

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}

TEST(FileWriterTest, TestOpenCloseFile) {
    std::string testFileName = "test_output.txt";

    // Удаляем файл, если он существует
    remove(testFileName.c_str());

    FileWriter fileWriter(testFileName);
    EXPECT_NO_THROW(fileWriter.open()); // Открытие не должно вызывать исключение
    fileWriter.close(); // Закрываем файл
    EXPECT_NO_THROW(fileWriter.close()); // Проверка, что закрытие не вызывает исключение

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}

TEST(FileWriterTest, TestWriteToFileWithoutOpening) {
    std::string testFileName = "test_output.txt";

    // Удаляем файл, если он существует
    remove(testFileName.c_str());

    FileWriter fileWriter(testFileName);
    EXPECT_NO_THROW(fileWriter.writeStatisticToCSV({}, 0)); // Запись без открытия не должна вызывать исключение

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}
