#include <queue>
#include <chrono> 

#include "search_strategy.h"
#include "utilities.h"
#include "aho_corasick.h"

void AhoCorasick::add_string(const std::string &keyword, int keywordId)
{
    int curNode = 0; //start at root
    for (const char &c: keyword)
    {
        int cIndex = c - START_CHAR;
        if (trie[curNode].child[cIndex] == -1) //does not exist
        {
            trie[curNode].child[cIndex] = trie.size();
            trie.emplace_back(); //create a new node in trie
        }
        curNode = trie[curNode].child[cIndex];
    }
    trie[curNode].found_word_id.push_back(keywordId); 
}

void AhoCorasick::build_automaton()
{
    std::queue <int> waitToVisit;
    trie[0].fail = 0;

    //initialize next[i] of direct child of root.
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (trie[0].child[i] != -1)
        {
            int curNode = trie[0].child[i];
            trie[curNode].fail = 0;
            trie[0].next[i] = curNode;
            waitToVisit.push(curNode); 
        }
        else 
        {
            trie[0].next[i] = 0; //comback to root
        }
    }

    //BFS-based traversal
    while (!waitToVisit.empty())
    {
        int u = waitToVisit.front();
        waitToVisit.pop();
        for (int i = 0; i < ALPHABET_SIZE; ++i)
        {
            if (trie[u].child[i] != -1) //have been existed in trie
            {
                int v = trie[u].child[i];
                trie[v].fail = trie[trie[u].fail].next[i];
                
                if (!trie[trie[v].fail].found_word_id.empty())
                {
                    trie[v].dict_link = trie[v].fail;
                }
                else 
                {
                    trie[v].dict_link = trie[trie[v].fail].dict_link;
                }

                trie[u].next[i] = v; //go to v
                waitToVisit.push(v); 
            }
            else //have not been existed in trie
            {
                trie[u].next[i] = trie[trie[u].fail].next[i]; 
            }
        }
    }
}

void AhoCorasick::match_string(int length, const std::function <char(int)> &get_char, int curRow, int curCol, int dr, int dc, Output &result)
{
    int cur = 0;
    for (int i = 0; i < length; ++i)
    {
        ++result.comparisons;
        int index = get_char(i) - START_CHAR;
        cur = trie[cur].next[index];

        int tmp = cur;
        while (tmp != 0)
        {
            if (!trie[tmp].found_word_id.empty()) //found keyword
            {
                for (int id: trie[tmp].found_word_id)
                {
                    int wordLength = result.listOfKey[id].keyWord.size();
                    //find coordinate on the grid
                    int startRow = curRow + (i - wordLength + 1) * dr;
                    int startCol = curCol + (i - wordLength + 1) * dc;
                    int endRow = curRow + i * dr;
                    int endCol = curCol + i * dc;
    
                    result.listOfKey[id].locations.push_back({startRow, startCol, endRow, endCol});
                }
            }
            tmp = trie[tmp].dict_link;
        }
    }
}

Output AhoCorasick::locate_keywords(const Input &data) 
{
    Output result;
    result.comparisons = 0;
    result.algorithm = get_name();

    auto start = std::chrono::high_resolution_clock::now(); //time
    
    trie.clear(); //delete old data (neu co)
    trie.emplace_back(); //create root
    int patternId = 0;
    for (const std::string &pattern: data.keyWord)
    {
        add_string(pattern, patternId++); //build trie
        Key key;
        key.keyWord = pattern;
        result.listOfKey.push_back(key); //add keywords to the results (excluding position)
    }

    build_automaton();

    for (int r = 0; r < data.nRow; ++r)
    {
        //lambda function to get text[i]
        std::function <char(int)> get_row_char = [&](int i) { return data.puzzleGrid[r][i]; };
        match_string(data.nCol, get_row_char, r, 0, 0, 1, result); 
    }

    for (int c = 0; c < data.nCol; ++c)
    {
        std::function <char(int)> get_col_char = [&](int i) { return data.puzzleGrid[i][c]; };
        match_string(data.nRow, get_col_char, 0, c, 1, 0, result); 
    }

    //calculate time execute
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    result.executionTime = elapsed.count();

    return result;
}

std::string AhoCorasick::get_name() 
{
    return "Aho Corasick";
}