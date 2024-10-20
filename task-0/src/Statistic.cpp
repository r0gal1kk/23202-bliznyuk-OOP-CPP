#include "Statistic.h"
#include <algorithm>

Statistic::Statistic() : wordsTotal(0) {}

void Statistic::push(const std::string& word) {
    wordsMap[word]++;
    wordsTotal++;
}

void Statistic::pushVector(const std::vector<std::string>& splittedString) {
    for (const auto& key : splittedString) {
        wordsMap[key]++;
    }
    wordsTotal += splittedString.size();
}

double Statistic::getPercentage(const std::string& word) {
    if (!wordsMap.count(word)) {
        return 0;
    }
    return (static_cast<double>(wordsMap[word]) / wordsTotal) * PERCENT;
}

std::vector<std::string> Statistic::convertToVector(const std::vector<std::pair<std::string, int> > &statisticVector) {
    std::vector<std::string> result(statisticVector.size() + 1);
    result[0] = "Word,Frequency,Percentage\n";
    int index = 1;
    for (auto element : statisticVector) {
        result[index++] = element.first + ',' + std::to_string(element.second) + ',' + std::to_string(getPercentage(element.first)) + "%\n";
    }
    return result;
}

std::vector<std::string> Statistic::getStats() {
    std::vector<std::pair<std::string, int>> statisticVector(wordsMap.size());
    sortMapByValue(statisticVector);
    return convertToVector(statisticVector);
}

unsigned long long Statistic::getWordsTotal() {
    return wordsTotal;
}

void Statistic::convertMapIntoVector(std::vector<std::pair<std::string, int>>& statisticVector) {
    int index = 0;
    for (const auto& element : wordsMap) {
        statisticVector[index++] = element;
    }
}

bool Statistic::comparePairs(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void Statistic::sortMapByValue(std::vector<std::pair<std::string, int>>& statisticVector) {
    convertMapIntoVector(statisticVector);
    std::sort(statisticVector.begin(), statisticVector.end(), comparePairs);
}
