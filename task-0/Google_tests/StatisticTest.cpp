#include <gtest/gtest.h>
#include "Statistic.h"

TEST(StatisticTest, TestPush) {
    Statistic statistic;
    statistic.push("test");
    statistic.push("example");
    statistic.push("test");

    EXPECT_EQ(statistic.getWordsTotal(), 3);
}

TEST(StatisticTest, TestPushVector) {
    Statistic statistic;
    statistic.push("test");
    statistic.push("example");

    std::vector<std::string> words = {"another", "test", "example", "test"};
    statistic.pushVector(words);

    EXPECT_DOUBLE_EQ(statistic.getPercentage("test"), 50.0);
    EXPECT_EQ(statistic.getWordsTotal(), 6);
}

TEST(StatisticTest, TestGetStats) {
    Statistic statistic;
    statistic.push("test");
    statistic.push("example");
    statistic.push("test");
    std::vector<std::pair<std::string, int>> stats = statistic.getStats();

    EXPECT_EQ(stats[0].first, "test");
    EXPECT_EQ(stats[1].first, "example");
    EXPECT_EQ(stats[0].second, 2);
    EXPECT_EQ(stats[1].second, 1);
}

    TEST(StatisticTest, TestGetPercentageNonExistentWord) {
    Statistic statistic;
    statistic.push("test");

    EXPECT_EQ(statistic.getPercentage("nonexistent"), 0);
}
