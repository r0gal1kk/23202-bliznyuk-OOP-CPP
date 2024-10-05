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

    FileWriter writer(argv[2]);
    writer.open();
    writer.write(statistic.getStats());
    writer.close();

    return 0;
}
