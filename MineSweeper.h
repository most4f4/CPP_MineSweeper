#ifndef STDD_MINESWEEPER_H
#define STDD_MINESWEEPER_H

#include <cstddef>
#include <iostream>
#include <string>

namespace stdd{

    size_t digForTreasure(const std::string& str, char mark);
    size_t digForMine(const std::string& str, int num, char mark);

    class MineSweeper{
        size_t rows = 0;
        size_t colSize = 0;
        std::string* map = nullptr;
    public:
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
    };

}

#endif