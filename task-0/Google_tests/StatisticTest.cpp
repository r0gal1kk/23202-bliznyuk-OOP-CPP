#include <gtest/gtest.h>
#include "Statistic.h"

TEST(StatisticTest, TestPushWord) {
    Statistic statistic;
    statistic.pushWord("test");
    statistic.pushWord("example");
    statistic.pushWord("test");

    EXPECT_EQ(statistic.getWordsTotal(), 3);
}

TEST(StatisticTest, TestPushWordsVector) {
    Statistic statistic;
    statistic.pushWord("test");
    statistic.pushWord("example");

    std::vector<std::string> words = {"another", "test", "example", "test"};
    statistic.pushWordsVector(words);

    EXPECT_DOUBLE_EQ(statistic.getFreqency("test"), 50.0);
    EXPECT_EQ(statistic.getWordsTotal(), 6);
}

TEST(StatisticTest, TestGetSortedStatistic) {
    Statistic statistic;
    statistic.pushWord("test");
    statistic.pushWord("example");
    statistic.pushWord("test");

    auto sortedStatistic = statistic.getSortedStatistic();

    EXPECT_EQ(sortedStatistic[0].first, "test");
    EXPECT_EQ(sortedStatistic[0].second, 2);
    EXPECT_EQ(sortedStatistic[1].first, "example");
    EXPECT_EQ(sortedStatistic[1].second, 1);
}

TEST(StatisticTest, TestGetFrequencyNonExistentWord) {
    Statistic statistic;
    statistic.pushWord("test");

    EXPECT_EQ(statistic.getFreqency("nonexistent"), 0);
}
