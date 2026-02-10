#ifndef COMMAND_LINE_PARSER_H 
#define COMMAND_LINE_PARSER_H

#include "utilities.h"

bool isValidAlgorithm(std::string algorithm);
Config loadConfig(int argc, char* argv[]);

#endif
