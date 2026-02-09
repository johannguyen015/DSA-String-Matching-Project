#include <iostream>

#include "command_line_parser.h"
#include "file_manager.h"

int main(int argc, char* argv[])
{
    try
    {
        Config config = loadConfig(argc, argv);
        Input data = readFile(config.inputFile);
        ///DO SOMETHING
        // writeFile(config.outputFile, result);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Please check and try again later." << '\n';
        return 1;
    }

    return 0;
}
