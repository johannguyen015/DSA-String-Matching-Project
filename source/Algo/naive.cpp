#include "search_strategy.h"
#include "utilities.h"
#include "naive.h"
#include <chrono>

using namespace std;

Output Naive::locate_keywords(const Input &data) 
{
    using namespace std::chrono;
    Output result;
    result.algorithm = "Naive";
    result.comparisons = 0;
    auto startTime = high_resolution_clock::now();

    for (int m = 0; m < data.nKeyword; m++)
    {
        Key currentKeyword;
        currentKeyword.keyWord = data.keyWord[m];
        int lenKeyword = data.keyWord[m].size();

        //search horizontal
        for (int i = 0; i < data.nRow; i++)
        {
            for (int j = 0; j <= data.nCol - lenKeyword; j++)
            {
                bool isAppear = true;
                for (int k = 0; k < lenKeyword; k++)
                {
                    result.comparisons++;
                    if (currentKeyword.keyWord[k] != data.puzzleGrid[i][j + k])
                    {
                        isAppear = false;
                        break;
                    }
                }
                if(isAppear)
                {
                    Point newPoint;
                    newPoint.startRow = i;
                    newPoint.endRow = i;
                    newPoint.startCol = j;
                    newPoint.endCol = j + lenKeyword - 1;
                    currentKeyword.locations.push_back(newPoint);
                }
            }
        }

        //search vertical
        for (int i = 0; i < data.nCol; i++)
        {
            for (int j = 0; j <= data.nRow - lenKeyword; j++)
            {
                bool isAppear = true;
                for (int k = 0; k < lenKeyword; k++)
                {
                    result.comparisons++;
                    if (currentKeyword.keyWord[k] != data.puzzleGrid[j + k][i])
                    {
                        isAppear = false;
                        break;
                    }
                }
                if (isAppear)
                {
                    Point newPoint;
                    newPoint.startRow = j;
                    newPoint.endRow = j + lenKeyword - 1;
                    newPoint.startCol = i;
                    newPoint.endCol = i;
                    currentKeyword.locations.push_back(newPoint);
                }
            }
        }
        result.listOfKey.push_back(currentKeyword);
    }
    
    auto endTime = high_resolution_clock::now();
    duration<double, milli> exeTime = endTime - startTime;
    result.executionTime = exeTime.count();

    return result;
}

std::string Naive::get_name() 
{
    return "Navie";
}