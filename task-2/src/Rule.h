#ifndef RULE_H
#define RULE_H

#include <unordered_set>
#include <string>

class Rule {
private:
    std::unordered_set<int> birthRules;
    std::unordered_set<int> survivalRules;
public:
    Rule() = default;
    Rule(const std::string& birthRule, const std::string& survivalRule);

    bool shouldBorn(const int& liveNeighbours) const;
    bool shouldSurvive(const int& liveNeighbours) const;
    std::string getRuleString() const;
};

#endif // RULE_H
