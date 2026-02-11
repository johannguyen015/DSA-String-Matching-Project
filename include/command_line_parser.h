#ifndef COMMAND_LINE_PARSER_H 
#define COMMAND_LINE_PARSER_H

#include "utilities.h"

bool is_valid_algorithm(std::string algorithm);
Config load_config(int argc, char* argv[]);

#endif
