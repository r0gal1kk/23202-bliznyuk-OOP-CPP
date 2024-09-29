#include "Parser.h"
#include <algorithm>
#include <cctype>

void Parser::toLowerString(std::string& line) {
    std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
}

void Parser::splitIntoWords(const std::string& line, std::vector<std::string>& splittedString) {
    std::string currentWord;
    for (unsigned char symbol : line) {
        if (std::isalnum(symbol)) {
            currentWord += symbol;
        } else {
            if (!currentWord.empty()) {
                splittedString.push_back(currentWord);
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        splittedString.push_back(currentWord);
    }
}

std::vector<std::string> Parser::getSplittedString(std::string& line) {
    std::vector<std::string> splittedString;
    toLowerString(line);
    splitIntoWords(line, splittedString);
    return splittedString;
}
