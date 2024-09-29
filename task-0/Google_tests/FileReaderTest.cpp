#include "FileReader.h"
#include <gtest/gtest.h>
#include <fstream>

TEST(FileReaderTest, TestOpenFile) {
    std::string testFileName = "test_file.txt";

    // Создание тестового файла
    std::ofstream testFile(testFileName);
    testFile << "First line\n";
    testFile.close();

    FileReader fileReader(testFileName);
    fileReader.open();
    EXPECT_TRUE(fileReader.hasNext());

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}

TEST(FileReaderTest, TestReadLines) {
    std::string testFileName = "test_file.txt";

    // Создание тестового файла
    std::ofstream testFile(testFileName);
    testFile << "First line\nSecond line\nThird line";
    testFile.close();

    FileReader fileReader(testFileName);
    fileReader.open();

    EXPECT_TRUE(fileReader.hasNext());
    EXPECT_EQ(fileReader.getNextString(), "First line");

    EXPECT_TRUE(fileReader.hasNext());
    EXPECT_EQ(fileReader.getNextString(), "Second line");

    EXPECT_TRUE(fileReader.hasNext());
    EXPECT_EQ(fileReader.getNextString(), "Third line");

    EXPECT_FALSE(fileReader.hasNext());
    fileReader.close();

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}

TEST(FileReaderTest, TestCloseFile) {
    std::string testFileName = "test_file.txt";

    // Создание тестового файла
    std::ofstream testFile(testFileName);
    testFile << "Test line\n";
    testFile.close();

    FileReader fileReader(testFileName);
    fileReader.open();
    EXPECT_TRUE(fileReader.hasNext());

    fileReader.close();
    EXPECT_NO_THROW(fileReader.close()); // Проверка, что закрытие не вызывает исключение

    // Удаление тестового файла после проверки
    remove(testFileName.c_str());
}

TEST(FileReaderTest, TestOpenNonExistentFile) {
    FileReader fileReader("non_existent_file.txt");
    EXPECT_NO_THROW(fileReader.open()); // Открытие не должно вызывать исключение
    EXPECT_FALSE(fileReader.hasNext()); // Файл не существует, следовательно, строк не будет
}
