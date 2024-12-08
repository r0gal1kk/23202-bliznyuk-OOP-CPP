#include "Rule.h"

Rule::Rule(const std::string& birthRule, const std::string& survivalRule) {
    for (const auto c : birthRule) {
        if (isdigit(c)) {
            birthRules.insert(c - '0');
        }
    }
    for (const auto c : survivalRule) {
        if (isdigit(c)) {
            survivalRules.insert(c - '0');
        }
    }
}

bool Rule::shouldBorn(const int& liveNeighbours) const {
    return birthRules.count(liveNeighbours);
}

bool Rule::shouldSurvive(const int& liveNeighbours) const {
    return survivalRules.count(liveNeighbours);
}

std::string Rule::getRuleString() const {
    std::string result = "#R B";
    for (const auto& rule : birthRules) {
        result += std::to_string(rule);
    }
    result += "/S";
    for (const auto& rule : survivalRules) {
        result += std::to_string(rule);
    }
    return result;
}
