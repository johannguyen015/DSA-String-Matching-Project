#ifndef KMP_H
#define KMP_H 

#include "search_strategy.h"
#include "utilities.h"

class  KnuthMorrisPratt : public SearchStrategy //inherits from SearchStrategy
{
public: 
    //query
    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
};

#endif