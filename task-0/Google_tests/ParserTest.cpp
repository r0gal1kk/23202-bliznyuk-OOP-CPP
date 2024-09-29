#include "Parser.h"
#include <gtest/gtest.h>

TEST(ParserTest, TestGetSplittedString) {
    Parser parser;

    std::string input = "Hello World!";
    std::vector<std::string> result = parser.getSplittedString(input);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "world");

    input = "Test 123, test.";
    result = parser.getSplittedString(input);
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "test");
    EXPECT_EQ(result[1], "123");
    EXPECT_EQ(result[2], "test");

    input = "";
    result = parser.getSplittedString(input);
    EXPECT_TRUE(result.empty());

    input = "    Leading and trailing spaces    ";
    result = parser.getSplittedString(input);
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "leading");
    EXPECT_EQ(result[1], "and");
    EXPECT_EQ(result[2], "trailing");
    EXPECT_EQ(result[3], "spaces");
}

TEST(ParserTest, TestGetSplittedStringWithPunctuation) {
    Parser parser;

    std::string input = "Hello, player1! How is it going?";
    std::vector<std::string> result = parser.getSplittedString(input);
    EXPECT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], "hello");
    EXPECT_EQ(result[1], "player1");
    EXPECT_EQ(result[2], "how");
    EXPECT_EQ(result[3], "is");
    EXPECT_EQ(result[4], "it");
    EXPECT_EQ(result[5], "going");
}
