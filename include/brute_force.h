#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H 

#include "search_strategy.h"
#include "utilities.h"

class  Brute_force : public SearchStrategy //inherits from SearchStrategy
{
public: 
    Brute_force() = default;
    ~Brute_force() = default;

    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
};

#endif