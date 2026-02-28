#include <chrono> 

#include "search_strategy.h"
#include "utilities.h"
#include "boyer_moore.h"

const int NO_OF_CHARS = 256;

void BoyerMoore::build_bad_character(const std::string &pattern, int *badChar) { 
    for (int i = 0; i < NO_OF_CHARS; i++) 
        badChar[i] = -1;
    
    for (int i = 0; i < pattern.size();i++) 
        badChar[(unsigned char)pattern[i]] = i;
}

//bPos[i] stores the starting index of the border for the suffix starting at position i in the given pattern P
//shift[i] stores the distance the pattern will shift when a mismatch occurs at position i-1
void BoyerMoore::build_good_suffix(const std::string &pattern, std::vector <int> &shift) { 
    int i = pattern.size(), j = pattern.size() + 1;
    std::vector <int> bPos(pattern.size() + 1);
    bPos[i] = j;
    while (i > 0) 
    {
        while (j <= pattern.size() && pattern[i - 1] != pattern[j - 1]) 
        {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = bPos[j];
        }
        i--;
        j--;
        bPos[i] = j;
    }

    j = bPos[0];
    for (int i = 0; i <= pattern.size(); i++) 
    {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j) 
            j = bPos[j];
    }
}


//return first position of occur
std::vector <int> BoyerMoore::match_string(int lengthT, int lengthP, const std::function <char(int)> &get_char, const std::string &pattern, const std::vector <int> &shift, int *badChar, long long &comparisons) { 
    std::vector <int> result;
    int s = 0, j;
    while (s <= lengthT - lengthP) 
    {
        j = lengthP - 1;
        while (j >= 0) 
        {
            comparisons++;
            if (pattern[j] == get_char(s + j))
            {
                j--;
            }
            else 
            {
                break;
            }
        }
        if (j < 0) 
        {
            result.push_back(s);
            s += shift[0];
        }
        else 
        {
            unsigned char x = get_char(s + j);
            int badCharacterShift = std::max(1, j - badChar[x]);
            int goodSuffixShift = shift[j + 1];
            
            s += std::max(badCharacterShift, goodSuffixShift);
        }
    }

    return result;

}

///implement the functions
Output BoyerMoore::locate_keywords(const Input &data) 
{
    //std::cout << "Hello world";
    Output result;
    result.comparisons = 0;
    result.algorithm = get_name();

    auto start = std::chrono::high_resolution_clock::now(); //time

    for (const std::string &pattern: data.keyWord) 
    {
        int lengthP = pattern.size();
        std::vector <int> shift(lengthP + 1, 0);
        int badChar[NO_OF_CHARS];
        
        build_bad_character(pattern, badChar);
        build_good_suffix(pattern, shift);

        Key curKey;
        curKey.keyWord = pattern;

        //horizontal (left to right)
        if (pattern.size() <= data.nCol) 
        {
            for (int r = 0; r < data.nRow; r++) 
            {
                std::function <char (int)> get_row_char = [&](int i) {return data.puzzleGrid[r][i]; };
                std::vector <int> index = match_string(data.nCol, lengthP, get_row_char, pattern, shift, badChar, result.comparisons);

                for (int id: index) {
                    Point curKeywordLocation;
                    //find coordinate on the grid
                    curKeywordLocation.startRow = curKeywordLocation.endRow = r;
                    curKeywordLocation.startCol = id;
                    curKeywordLocation.endCol = id + pattern.size() - 1;
                    curKey.locations.push_back(curKeywordLocation);
                }
            }
        }
        if (pattern.size() <= data.nRow)
        {
            for (int c = 0; c < data.nCol; ++c)
            {
                std::function <char(int)> get_col_char = [&](int i) { return data.puzzleGrid[i][c]; };
                std::vector <int> index = match_string(data.nRow, lengthP, get_col_char, pattern, shift, badChar, result.comparisons);
    
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
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    result.executionTime = elapsed.count();
    return result;
}

std::string BoyerMoore::get_name() 
{
    return "Boyer Moore";
}