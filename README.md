# DSA String Matching Project

A modular C++ project implementing classic **string matching algorithms** using the Strategy Design Pattern.

This project is designed for studying, implementing, and comparing different pattern matching algorithms in a clean and extensible architecture.

---

## 📌 Features

- Object-Oriented Design
- Strategy Pattern implementation
- Easily extendable for new algorithms
- Command-line input/output handling
- Modular project structure
- Built with C++17

---

## 🛠 Requirements

- C++17 compatible compiler (**g++ 9+ recommended**)
- Windows environment (uses `build.bat`)
- MinGW / MSYS2 or any environment supporting `g++`
- Git (for version control)

Compilation standard: **-std=c++17**

## Project Structure

```text
DSA-String-Matching-Project/
│
├── include/                      # Header files
│   ├── utilities.h
│   ├── command_line_parser.h
│   ├── file_manager.h
│   ├── search_strategy.h
│   ├── naive.h
│   ├── rabin_karp.h
│   ├── kmp.h
│   └── boyer_moore.h
│
├── source/                       # Implementation files
│   ├── main.cpp
│   ├── command_line_parser.cpp
│   ├── file_manager.cpp
│   └── Algo/
│       ├── naive.cpp
│       ├── rabin_karp.cpp
│       ├── kmp.cpp
│       └── boyer_moore.cpp
│
├── data/                         # Sample input/output files
│   ├── puzzle.txt
│   └── solution.txt
│
├── bin/                          # Compiled executable output
├── build.bat                     # Build & run script
└── README.md
```

## 📝 Code Conventions

| Element | Convention | Rule | Example |
| :--- | :--- | :--- | :--- |
| **Functions** | `snake_case` | Starts with a verb. | `calculate_hash()`, `is_valid_string()` |
| **Variables** | `camelCase` | Noun. | `patternLength`, `textBuffer` |
| **Constants** | `UPPER_SNAKE_CASE` | All caps, noun. | `MAX_STRING_LENGTH`, `PRIME_BASE` |
| **Classes / Structs** | `PascalCase` | Noun. | `StringMatcher`, `SuffixTreeNode` |
| **Booleans** | `camelCase` | Prefix with `is`, `has`, `should`, `can`. | `isMatchFound`, `hasProcessed` |
| **Files / Directories** | `snake_case` | Lowercase. | `rabin_karp.cpp`, `string_utils.h` |

## How to use

### 1. Clone the repository

```bash
git clone https://github.com/johannguyen015/DSA-String-Matching-Project.git
```

### 2. Create your own branch

```bash
git checkout -b algorithm/<your-algorithm-name>
```
Example:
```bash
git checkout -b algorithm/naive
```

### 3. Implement Your Algorithm

- Code into an existing .h and .cpp file (naive, rabin karp, kmp, boyer moore)
- Implement required functions:
    - Output locateKeywords(const Input &data) override;
    - std::string getName() override;
- You may add additional helper functions if needed
- Make sure your implementation is consistent with the existing architecture

### 4. Build & Run

- You can double click on file build.bat in your explorer or run ".\build.bat" in terminal
- To test your algorithm, change *kmp* in build.bat into your algorithm

Example:

```bash
bin\main.exe -i data/puzzle.txt -a naive -o data/solution.txt
```

### 5. Push Your Code

```bash
git add .
git commit -m "Add <your-algorithm-name>"
git push origin algorithm/<your-algorithm-name>
```
