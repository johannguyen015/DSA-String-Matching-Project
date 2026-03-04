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
    auto startTime = high_resolution_clock::now();

    //search keyword
    for (int m = 0; m < data.nKeyword; m++)
    {
        Key currKeyword;
        currKeyword.keyWord = data.keyWord[m];

        int lenKeyword = data.keyWord[m].size();
        //Check if the keyword longer than data
        if (lenKeyword > data.nRow && lenKeyword > data.nCol)
        {
            result.listOfKey.push_back(currKeyword);
            continue;
        }

        long long keywordHash = compute_data_hash(data.keyWord[m], lenKeyword);
        long long powerLen = power_by_base(lenKeyword - 1);

        //search horizontal
        if (lenKeyword <= data.nCol)
        {
            for (int i = 0; i < data.nRow; i++)
            {
                long long currentHash = 0;
                for (int j = 0; j < data.nCol; j++)
                {
                    bool isAppear = false;
                    if (j < lenKeyword)
                    {
                        int lowOder = char_to_int(data.puzzleGrid[i][j]);
                        currentHash = add(multiple(currentHash, BASE), lowOder);
                        if (j < lenKeyword - 1) continue;
                    }
                    else
                    {
                        int idHighOder = j - lenKeyword;
                        int highOder = char_to_int(data.puzzleGrid[i][idHighOder]);
                        int lowOder = char_to_int(data.puzzleGrid[i][j]);

                        //rule out the high-oder number
                        currentHash = subtract(currentHash, multiple(highOder, powerLen));
                        //add the low-oder number
                        currentHash = add(multiple(currentHash, BASE), lowOder);
                    }

                    if (keywordHash == currentHash)
                    {
                        isAppear = true;
                        for (int k = 0; k < lenKeyword; k++)
                        {
                            result.comparisons++;
                            if (currKeyword.keyWord[k] != data.puzzleGrid[i][j - lenKeyword + 1 + k])
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
        }

        //search vertical
        if (lenKeyword <= data.nRow)
        {
            for (int i = 0; i < data.nCol; i++)
            {
                long long currentHash = 0;

                for (int j = 0; j < data.nRow; j++)
                {
                    bool isAppear = false;
                    if (j < lenKeyword)
                    {
                        int lowOder = char_to_int(data.puzzleGrid[j][i]);
                        currentHash = add(multiple(currentHash, BASE), lowOder);
                        if (j < lenKeyword - 1) continue;
                    }
                    else
                    {
                        int idHighOder = j - lenKeyword;
                        int highOder = char_to_int(data.puzzleGrid[idHighOder][i]);
                        int lowOder = char_to_int(data.puzzleGrid[j][i]);

                        //rule out the high-oder number
                        currentHash = subtract(currentHash, multiple(highOder, powerLen));
                        //add the low-oder number
                        currentHash = add(multiple(currentHash, BASE), lowOder);
                    }

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