#include <fstream>
#include <string>
#include <stdexcept>
#include <iomanip>

#include "utilities.h"

Input read_file(const std::string &fileName)
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        throw std::runtime_error(fileName + " not found!");
    }
    
    Input data;
    inputFile >> data.nRow >> data.nCol;
    data.puzzleGrid.resize(data.nRow, std::vector <char> (data.nCol));
    for (int i = 0; i < data.nRow; ++i)
    {
        for (int j = 0; j < data.nCol; ++j)
        {
            inputFile >> data.puzzleGrid[i][j];
        }
    }
    inputFile >> data.nKeyword;
    data.keyWord.resize(data.nKeyword);
    for (int i = 0; i < data.nKeyword; ++i)
    {
        inputFile >> data.keyWord[i];
    }

    inputFile.close();
    return data;
}

void write_file(const std::string &fileName, const Output &data)
{
    std::ofstream outFile(fileName);
    if (!outFile.is_open())
    {
        throw std::runtime_error(fileName + " not found!");
    }

    for (const Key &key: data.listOfKey)
    {
        outFile << key.keyWord << ": ";
        if (key.locations.empty())
        {
            outFile << "not found";
        }
        else
        {
            for (const Point &point: key.locations)
            {
                outFile << '(' << point.startRow << ", " << point.startCol << ") -> (" << point.endRow << ", " << point.endCol << "); ";
            }
        }
        outFile << '\n';
    }

    outFile << "--------------------------------" << '\n';
    outFile << "Algorithm: " << data.algorithm << '\n';
    outFile << "Comparisons: " << data.comparisons << '\n';
    outFile << "Execution Time: " << std::fixed << std::setprecision(2) << data.executionTime << " ms" << '\n';

    outFile.close();
}