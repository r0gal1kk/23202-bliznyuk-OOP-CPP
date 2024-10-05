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

    std::string str = "word1,2,40%\nword2,3,60%\n";
    unsigned long long wordsTotal = 5;
    fileWriter.write(str);
    fileWriter.close();

    // Проверяем, что файл был создан и содержит ожидаемые данные
    std::ifstream inFile(testFileName);
    ASSERT_TRUE(inFile.is_open());

    std::string line;
    std::getline(inFile, line);
    EXPECT_EQ(line, "word1,2,40%");

    std::getline(inFile, line);
    EXPECT_EQ(line, "word2,3,60%");

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
    EXPECT_NO_THROW(fileWriter.write("word")); // Запись без открытия не должна вызывать исключение

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}
