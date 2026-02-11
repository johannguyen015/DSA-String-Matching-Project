#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include "search_strategy.h"
#include "utilities.h"

class  RabinKarp : public SearchStrategy //inherits from SearchStrategy
{
public: 
    //query
    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
};

#endif