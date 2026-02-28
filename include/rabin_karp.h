#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include "search_strategy.h"
#include "utilities.h"

class  RabinKarp : public SearchStrategy //inherits from SearchStrategy
{
private:
	//constants for Rabin Karp (hashing)
    const long long MOD = 2147483647;
    const int BASE = 29;

	//arithmetic operations with modulo to avoid overflow
    long long add(long long a, long long b);
    long long multiple(long long a, long long b);
    long long subtract(long long a, long long b);

	//Rabin Karp specific functions
    long long power_by_base(int space);
    int char_to_int(char c);
    long long compute_data_hash(std::string data, int lenData);

public: 
	RabinKarp() = default;
	~RabinKarp() = default;

    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
};

#endif