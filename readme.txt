The submission file size exceeds Moodle's limit. You can download the full project archive here: https://github.com/johannguyen015/DSA-String-Matching-Project/tree/submit.
----------------------
1. INSTALLATION & COMPILATION GUIDE

The project is written strictly in C/C++ without any non-standard libraries. It is built to be compiled using the GNU g++ compiler with the C++17 standard.

Step 1: Download the project folder from the GitHub repository link provided above.
Step 2: Open your terminal or command prompt.
Step 3: Navigate to the root folder of this project.
Step 4: Run the following command to compile the code: g++ -std=c++17 -I include source/*.cpp source/Algo/*.cpp -o crossword.exe

(If compiling on Linux/macOS, use '-o crossword' instead of '-o crossword.exe').


2. USER GUIDE (HOW TO RUN)

This command-line tool reads a text-based grid and searches for a list of keywords in both Horizontal (Left-to-Right) and Vertical (Top-to-Bottom) directions.

Usage format:
    .\crossword.exe -a [algorithm] -i [input_file] -o [output_file]  (for Windows)
    ./crossword -a [algorithm] -i [input_file] -o [output_file]	     (for Linux/macOS)

Command-line Options:
    -a [algorithm]   : Select the string matching algorithm.
                       Supported values: bf (Brute-Force), rk (Rabin-Karp), kmp (Knuth-Morris-Pratt), bm (Boyer-Moore), ac (Aho-Corasick)
    -i [input_file]  : Path to the user-provided puzzle data file.
    -o [output_file] : Path where the search results and performance metrics will be saved.

Execution Example: .\crossword.exe -a kmp -i tests/puzzle.txt -o tests/solution.txt
		   ./crossword -a kmp -i tests/puzzle.txt -o tests/solution.txt



