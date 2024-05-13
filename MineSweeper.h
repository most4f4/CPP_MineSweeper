#ifndef STDD_MINESWEEPER_H
#define STDD_MINESWEEPER_H

#include <cstddef>
#include <iostream>
#include <string>

namespace stdd{

    class MineSweeper{
        size_t rows = 0;
        size_t colSize = 0;
        std::string* map = nullptr;
    public:
        MineSweeper() = default;
        MineSweeper(size_t num) : rows(num), colSize(num) {};
        MineSweeper(const char* filename);
        ~MineSweeper();
        std::string operator[](int i) const{
            return map[i % rows];
        }
        size_t size() const{
            return rows;
        }
        std::ostream& display(std::ostream& os) const;
        size_t findMine(char mark, const std::vector<int>& luckyNums);
        std::vector<int> generateLuckyNumbers() const;
        MineSweeper& readFile(const char* filename);
        void generateRandomMap();
        void setRowsCols(size_t num);
    };

}

#endif