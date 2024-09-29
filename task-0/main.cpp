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
        std::vector<std::string> splittedString = parser.getSplittedString(currentLine);
        statistic.pushWordsVector(splittedString);
    }

    reader.close();

    FileWriter writer(argv[2]);
    writer.open();
    std::vector<std::pair<std::string, int>> statisticVector = statistic.getSortedStatistic();
    writer.writeStatisticToCSV(statisticVector, statistic.getWordsTotal());
    writer.close();

    return 0;
}
