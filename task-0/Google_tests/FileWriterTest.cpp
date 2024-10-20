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

    std::vector <std::string> words(2);
    words[0] = "word1,2,40%\n";
    words[1] = "word2,3,60%\n";
    fileWriter.write(words);
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
    std::vector <std::string> words(1);
    words[0] = "word";
    FileWriter fileWriter(testFileName);
    EXPECT_NO_THROW(fileWriter.write(words)); // Запись без открытия не должна вызывать исключение

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}
