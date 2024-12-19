#include "CommandLineParser.h"
#include "Exceptions.h"
#include "SoundProcessor.h"

int main(int argc, char *argv[]) {
    try {
        CommandLineParser parser(argc, argv);
        const bool help = parser.parse();
        if (!help) {
            return 0;
        }
        SoundProcessor processor(parser.getConfigFile(), parser.getInputFiles(), parser.getOutputFile());
        processor.process();
    } catch (const Exceptions &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    return 0;
}
