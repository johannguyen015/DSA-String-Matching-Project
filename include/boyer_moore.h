#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H 

#include <vector>
#include <functional>
#include "search_strategy.h"
#include "utilities.h"

class  BoyerMoore : public SearchStrategy //inherits from SearchStrategy
{
public: 
    //query
    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
private: 
    void build_bad_character(const std::string &pattern, int *badChar); 
    void build_good_suffix(const std::string &pattern, std::vector <int> &shift);
    std::vector <int> match_string(int lengthT, int lengthP, const std::function <char(int)> &get_char, const std::string &pattern, const std::vector <int> &shift, int *badChar, long long &comparisons);
};

#endif