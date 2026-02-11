#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

#include "utilities.h"

Input read_file(const std::string &fileName);

void write_file(const std::string &fileName, const Output &data);

#endif