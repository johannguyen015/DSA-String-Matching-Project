#include "search_strategy.h"
#include "utilities.h"
#include "kmp.h"

///implement the functions
Output KnuthMorrisPratt::locateKeywords(const Input &data) 
{
    Output result;

    //do something
    result.algorithm = "kmp";
    result.comparisons = 10;
    result.executionTime = 3.02;

    return result;
}

std::string KnuthMorrisPratt::getName() 
{
    return "KMP";
}