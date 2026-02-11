#ifndef SEARCH_STRATEGY_H
#define SEARCH_STRATEGY_H

#include <string>

#include "utilities.h"

class SearchStrategy
{
public:
    virtual ~SearchStrategy() = default; //using compiler's default virtual destructor 
    virtual Output locate_keywords(const Input &data) = 0;
    virtual std::string get_name() = 0;
};

#endif