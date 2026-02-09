#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>

#include "utilities.h"

Input readFile(const std::string &fileName);

void writeFile(const std::string &fileName, const Output &data);

#endif