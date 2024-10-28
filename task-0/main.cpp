#include "FileReader.h"
#include "Statistic.h"
#include "Parser.h"
#include "FileWriter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    FileReader reader(argv[1]);
    reader.open();

    Statistic statistic;
    Parser parser;

    while (reader.hasNext()) {
        std::string currentLine = reader.getNextString();
        std::vector<std::string> parsedString = parser.parse(currentLine);
        statistic.pushVector(parsedString);
    }
    reader.close();

    std::vector<std::pair<std::string, int>> stats = statistic.getStats();
    std::vector<std::string> strings(stats.size() + 1);
    strings[0] = "Word,Frequency,Percentage\n";
    int index = 1;
    for (auto element : stats) {
        strings[index++] = element.first + ',' + std::to_string(element.second) + ',' + std::to_string(statistic.getPercentage(element.first)) + "%\n";
    }

    FileWriter writer(argv[2]);
    writer.open();
    writer.write(strings);
    writer.close();

    return 0;
}
