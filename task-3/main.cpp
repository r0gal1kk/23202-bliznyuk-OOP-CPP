#include <iostream>
#include "CommandLineParser.h"
#include "SoundProcessor.h"

int main(int argc, char *argv[]) {
    const CommandLineParser parser(argc, argv);
    SoundProcessor processor(parser.getConfigFile(), parser.getInputFiles(), parser.getOutputFile());
    processor.process();
    return 0;
}
