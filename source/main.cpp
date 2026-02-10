#include <iostream>
#include <cassert>

#include "command_line_parser.h"
#include "file_manager.h"
#include "search_strategy.h"
#include "naive.h"
#include "rabin_karp.h"
#include "kmp.h"
#include "boyer_moore.h"

int main(int argc, char* argv[])
{
    SearchStrategy* searcher = nullptr;
    try
    {
        Config config = loadConfig(argc, argv);
        Input data = readFile(config.inputFile);
        //Choose algorithm
        if (config.algorithm == "bf")
        {
            searcher = new Naive();
        }
        else if (config.algorithm == "rk")
        {
            searcher = new RabinKarp();
        }
        else if (config.algorithm == "kmp")
        {
            searcher = new KnuthMorrisPratt();
        }
        else if (config.algorithm == "bm")
        {
            searcher = new BoyerMoore();
        }
        
        assert(searcher != nullptr && "choose algorithm unsuccessful"); 
        Output result = searcher->locateKeywords(data);
        writeFile(config.outputFile, result);
        delete searcher;
        searcher = nullptr;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << "Please check and try again later." << '\n';
        delete searcher;
        searcher = nullptr;
        return 1;
    }

    return 0;
}
