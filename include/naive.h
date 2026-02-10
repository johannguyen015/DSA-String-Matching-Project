#ifndef NAIVE_H
#define NAIVE_H 

#include "search_strategy.h"
#include "utilities.h"

class  Naive : public SearchStrategy //inherits from SearchStrategy
{
public: 
    //query
    Output locateKeywords(const Input &data) override;
    //returns the name of the algorithm
    std::string getName() override;
};

#endif