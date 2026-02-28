#ifndef KMP_H
#define KMP_H 

#include <vector>
#include <functional>

#include "search_strategy.h"
#include "utilities.h"

class  KnuthMorrisPratt : public SearchStrategy //inherits from SearchStrategy
{
public: 
    //query
    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
private:
    std::vector <int> build_lps(const std::string &partten);
    //match keywords with each string
    std::vector <int> match_string(int length, const std::function <char(int)> &get_char, const std::string &partten, const std::vector <int> &lps, long long &comparisons);
};

#endif