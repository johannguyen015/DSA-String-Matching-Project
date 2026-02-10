#include "utilities.h"

#include <stdexcept>

bool isValidAlgorithm(std::string algorithm)
{
    return algorithm == "bf" || algorithm == "rk" || algorithm == "kmp" || algorithm == "bm";
}

Config loadConfig(int argc, char* argv[])
{
    Config config;
    for (int i = 1; i < argc; ++i) //argv[0] is filename.exe
    {
        std::string arg = argv[i];
        if (arg == "-a" && i + 1 < argc)
        {
            config.algorithm = argv[++i];
        }
        else if (arg == "-i" && i + 1 < argc)
        {
            config.inputFile = argv[++i];
        }
        else if (arg == "-o" && i + 1 < argc)
        {
            config.outputFile = argv[++i];
        }
    }

    if (!isValidAlgorithm(config.algorithm) || config.inputFile.empty() || config.outputFile.empty())
    {
        throw std::runtime_error("Invalid arguments!");
    }

    return config;
}