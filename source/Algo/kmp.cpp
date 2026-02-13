#include <chrono>

#include "search_strategy.h"
#include "utilities.h"
#include "kmp.h"

//build longest prefix suffix array
std::vector <int> KnuthMorrisPratt::build_lps(const std::string &pattern)
{
    int m = pattern.size();
    std::vector <int> lps(m);
    int k = 0;
    lps[0] = 0;

    for (int i = 1; i < m; ++i)
    {
        while (k > 0 && pattern[i] != pattern[k])
        {
            k = lps[k - 1];
        }
        if (pattern[i] == pattern[k])
        {
            ++k;
        }
        lps[i] = k;
    }
    return lps; 
}

//length: size of text string
//get_char: function which access text[i]
std::vector <int> KnuthMorrisPratt::match_string(int length, const std::function <char(int)> &get_char, const std::string &pattern, const std::vector <int> &lps, long long &comparisons)
{
    std::vector <int> matches; //list of index pattern appear
    // if (length < pattern.size()) return matches;

    int m = pattern.size();
    int j = 0;

    for (int i = 0; i < length; ++i)
    {
        char currentChar = get_char(i); //equivalent to text[i]
        while (j > 0 && currentChar != pattern[j]) 
        {
            ++comparisons; //count
            j = lps[j - 1];
        }
        ++comparisons; //count
        if (currentChar == pattern[j])
        {
            ++j;
        }
        if (j == m)     
        {
            matches.push_back(i - m + 1);
            j = lps[j - 1];
        }
    }

    return matches;
}

Output KnuthMorrisPratt::locate_keywords(const Input &data) 
{
    Output result;
    result.comparisons = 0;
    result.algorithm = get_name();

    auto start = std::chrono::high_resolution_clock::now(); //time
    
    //traversal every keyword
    for (const std::string &pattern: data.keyWord)
    {
        std::vector <int> lps = build_lps(pattern);
        Key curKey;
        curKey.keyWord = pattern;
        
        //horizontal (left to right)
        if (pattern.size() <= data.nCol)
        {
            for (int r = 0; r < data.nRow; ++r)
            {      
                std::function <char(int)> get_row_char = [&](int i) { return data.puzzleGrid[r][i]; };
                std::vector <int> index = match_string(data.nCol, get_row_char, pattern, lps, result.comparisons);
    
                for (int id: index)
                {
                    Point curKeywordLocation;
                    //find coordinate on the grid
                    curKeywordLocation.startRow = curKeywordLocation.endRow = r;
                    curKeywordLocation.startCol = id;
                    curKeywordLocation.endCol = id + pattern.size() - 1;
                    curKey.locations.push_back(curKeywordLocation);
                }
            }
        }

        //vertical (top to bottom)
        if (pattern.size() <= data.nRow)
        {
            for (int c = 0; c < data.nCol; ++c)
            {
                std::function <char(int)> get_col_char = [&](int i) { return data.puzzleGrid[i][c]; };
                std::vector <int> index = match_string(data.nRow, get_col_char, pattern, lps, result.comparisons);
    
                for (int id: index)
                {
                    Point curKeywordLocation;
                    //find coordinate on the grid
                    curKeywordLocation.startCol = curKeywordLocation.endCol = c;
                    curKeywordLocation.startRow = id;
                    curKeywordLocation.endRow = id + pattern.size() - 1;
                    curKey.locations.push_back(curKeywordLocation);
                }
            }
        }
        result.listOfKey.push_back(curKey);
    }

    //calculate time execute
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    result.executionTime = elapsed.count();

    return result;
}

std::string KnuthMorrisPratt::get_name() 
{
    return "KMP";
}