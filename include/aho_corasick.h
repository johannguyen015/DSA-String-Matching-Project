#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H 

#include <functional>

#include "search_strategy.h"
#include "utilities.h"

class  AhoCorasick : public SearchStrategy //inherits from SearchStrategy
{
public: 
    static constexpr int ALPHABET_SIZE = 26; //'a' - 'z'
    static constexpr char START_CHAR = 'a';

public: 
    void add_string(const std::string& keyword, int keywordId);
    void build_automaton();
    void match_string(int length, const std::function <char(int)> &get_char, int curRow, int curCol, int dr, int dc, Output &result);

private:
    struct Node
    {
        int child[ALPHABET_SIZE]; //trie's node
        int next[ALPHABET_SIZE]; //deterministic finite automaton
        int fail; //failure link
        int dict_link;
        std::vector <int> found_word_id; //index of keyword appear in this node

        Node()
        {
            std::fill(child, child + ALPHABET_SIZE, -1);
            std::fill(next, next + ALPHABET_SIZE, -1);
            fail = 0;
            dict_link = 0;
        }
    };
    std::vector <Node> trie; 

public:
    //query
    Output locate_keywords(const Input &data) override;
    //returns the name of the algorithm
    std::string get_name() override;
};

#endif