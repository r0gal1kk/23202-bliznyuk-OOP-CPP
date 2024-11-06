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
