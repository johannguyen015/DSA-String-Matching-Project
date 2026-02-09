#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>

//Config info 
struct Config 
{
    std::string algorithm;
    std::string inputFile;
    std::string outputFile;
};

//Input structure
struct Input
{
    int nRow, nCol;
    std::vector <std::vector <char>>  puzzleGrid;
    int nKeyword;
    std::vector <std::string> keyWord;
};

//Output structure
struct Point
{
    int startRow, startCol;
    int endRow, endCol;
};

struct Key
{
    std::string keyWord;
    std::vector <Point> locations;
};

struct Output
{
    std::vector <Key> listOfKey;
    std::string algorithm;  
    long long comparisons;
    double executionTime;
};

#endif