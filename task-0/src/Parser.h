#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

class Parser {
private:
    void toLowerString(std::string& line);
    void splitIntoWords(const std::string& line, std::vector<std::string>& splittedString);
public:
    std::vector<std::string> parse(std::string& line);
};

#endif //PARSER_H
