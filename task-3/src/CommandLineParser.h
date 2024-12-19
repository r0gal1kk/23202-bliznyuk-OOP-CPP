#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <string>
#include <vector>

class CommandLineParser {
public:
    CommandLineParser(int argc, char* argv[]);
    std::string getConfigFile() const;
    std::string getOutputFile() const;
    std::vector<std::string> getInputFiles() const;

private:
    int argc;
    char** argv;
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    void parse();
    void printHelp() const;
    bool checkFormat(const std::string& arg, const std::string& format);
    bool showHelp;
};

#endif
