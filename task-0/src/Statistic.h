#ifndef STATISTIC_H
#define STATISTIC_H

#include <map>
#include <string>
#include <vector>
#include <utility>

class Statistic {
private:
    std::map<std::string, int> wordsMap;
    unsigned long long wordsTotal;
    const int PERCENT = 100;

    void convertMapIntoVector(std::vector<std::pair<std::string, int>>& statisticVector);
    static bool comparePairs(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);
    void sortMapByValue(std::vector<std::pair<std::string, int>>& statisticVector);
public:
    Statistic();
    void pushWord(const std::string& word);
    void pushWordsVector(const std::vector<std::string>& splittedString);
    double getFreqency(const std::string& word);
    std::vector<std::pair<std::string, int>> getSortedStatistic();
    unsigned long long getWordsTotal();
};

#endif //STATISTIC_H
