#include "search_strategy.h"
#include "utilities.h"
#include "rabin_karp.h"
#include <chrono>

using namespace std;

//arithmetic operations with modulo to avoid overflow
long long RabinKarp::add(long long a, long long b) 
{
    return (a + b) % MOD;
}

long long RabinKarp::multiple(long long a, long long b) 
{
    return (a * b) % MOD;
}

long long RabinKarp::subtract(long long a, long long b) 
{
    return (a - b + MOD) % MOD;
}

//Rabin Karp specific functions
long long RabinKarp::power_by_base(int space) 
{
    long long power = 1;
    for (int i = 0; i < space; i++)
        power = multiple(power, BASE);
    return power;
}

int RabinKarp::char_to_int(char c) 
{
    return (c - 'a' + 1);
}

long long RabinKarp::compute_data_hash(std::string data, int lenData) 
{
    long long Hash = 0;
    for (int i = 0; i < lenData; i++)
        Hash = add(multiple(Hash, BASE), char_to_int(data[i]));
    return Hash;
}

Output RabinKarp::locate_keywords(const Input &data) 
{
    using namespace std::chrono;
    Output result;
    result.comparisons = 0;
    result.algorithm = "Rabin-Karp";
    
    vector<vector<long long>> horizontalHash(data.nRow, vector<long long>(data.nCol));
    vector<vector<long long>> verticalHash(data.nRow, vector<long long>(data.nCol));
    auto startTime = high_resolution_clock::now();

    //compute horizontalHash
    for (int i = 0; i < data.nRow; i++)
    {
        horizontalHash[i][0] = char_to_int(data.puzzleGrid[i][0]);
        for (int j = 1; j < data.nCol; j++)
        {
            horizontalHash[i][j] = add(multiple(horizontalHash[i][j - 1], BASE), char_to_int(data.puzzleGrid[i][j]));
        }
    }
    //compute vertical horizontalHash
    for (int i = 0; i < data.nCol; i++)
    {
        verticalHash[0][i] = char_to_int(data.puzzleGrid[0][i]);
        for (int j = 1; j < data.nRow; j++)
        {
            verticalHash[j][i] = add(multiple(verticalHash[j - 1][i], BASE), char_to_int(data.puzzleGrid[j][i]));
        }
    }

    //search keyword
    for (int m = 0; m < data.nKeyword; m++)
    {
        Key currKeyword;
        currKeyword.keyWord = data.keyWord[m];

        int lenKeyword = data.keyWord[m].size();
        long long keywordHash = compute_data_hash(data.keyWord[m], lenKeyword);
        long long powerLen = power_by_base(lenKeyword);

        //search horizontal
        for (int i = 0; i < data.nRow; i++)
        {
            for (int j = lenKeyword - 1; j < data.nCol; j++)
            {
                bool isAppear = false;
                long long prefixHash = (j - lenKeyword >= 0) ? horizontalHash[i][j - lenKeyword] : 0;
                long long currentHash = subtract(horizontalHash[i][j], multiple(prefixHash, powerLen));
                if (keywordHash == currentHash)
                {
                    isAppear = true;
                    for (int k = 0; k < lenKeyword; k++)
                    {
                        result.comparisons++;
                        if (data.keyWord[m][k] != data.puzzleGrid[i][j - lenKeyword + 1 + k])
                        {
                            isAppear = false;
                            break;
                        }
                    }
                }
                if (isAppear)
                {
                    Point newPoint;
                    newPoint.startRow = i;
                    newPoint.endRow = i;
                    newPoint.startCol = j - lenKeyword + 1;
                    newPoint.endCol = j;
                    currKeyword.locations.push_back(newPoint);
                }
            }
        }

        //search vertical
        for (int i = 0; i < data.nCol; i++)
        {
            for (int j = lenKeyword - 1; j < data.nRow; j++)
            {
                bool isAppear = false;
                long long prefixHash = (j - lenKeyword >= 0) ? verticalHash[j - lenKeyword][i] : 0;
                long long currentHash = subtract(verticalHash[j][i], multiple(prefixHash, powerLen));
                if (keywordHash == currentHash)
                {
                    isAppear = true;
                    for (int k = 0; k < lenKeyword; k++)
                    {
                        result.comparisons++;
                        if (data.keyWord[m][k] != data.puzzleGrid[j - lenKeyword + 1 + k][i])
                        {
                            isAppear = false;
                            break;
                        }
                    }
                }
                if (isAppear)
                {
                    Point newPoint;
                    newPoint.startRow = j - lenKeyword + 1;
                    newPoint.endRow = j;
                    newPoint.startCol = i;
                    newPoint.endCol = i;
                    currKeyword.locations.push_back(newPoint);
                }
            }
        }
        result.listOfKey.push_back(currKeyword);
    }

    auto endTime = high_resolution_clock::now();
    duration<double, milli> exeTime = endTime - startTime;
    result.executionTime = exeTime.count();

    return result;
}

std::string RabinKarp::get_name() 
{
    return "Rabin Karp";
}