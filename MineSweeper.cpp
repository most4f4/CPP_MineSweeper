#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <future>
#include <functional>
#include <vector>
#include <numeric>
#include <cstdlib> // for std::rand
#include <ctime>   // for std::time
#include "MineSweeper.h"
#include "Utilities.h"

namespace stdd {

    MineSweeper::MineSweeper(const char* filename) {
        std::fstream fin(filename);
        if (fin) {
            fin >> rows;
            fin.ignore();
            map = new std::string[rows];
            size_t idx = 0;
            while (fin) {
                getline(fin, map[idx]);
                idx++;
            }
            colSize = map[0].length();
        }
        else {
            throw std::string(filename) + " cannot be opened";
        }
    }

    MineSweeper::~MineSweeper() {
        delete[] map;
    }

    std::ostream& MineSweeper::display(std::ostream& os) const {
        if (map) {
            for (size_t i = 0; i < rows; ++i) {
                os << "  " << map[i] << std::endl;
            }
        }
        else
            os << "The map is empty!" << std::endl;
        return os;
    }

    size_t MineSweeper::findMine(char mark, const std::vector<int>& luckyNums) {
        size_t count = 0;

        // Calculate the number of strings each thread will process
        size_t stringsPerThread = rows / 4;
        size_t remainder = rows % 4;

        // Define partitions of strings for each thread and futures
        std::vector<std::future<size_t>> futures;

        for (size_t i = 0; i < 4; ++i) {
            size_t startIdx = i * stringsPerThread;
            size_t endIdx = (i == 3) ? (startIdx + stringsPerThread + remainder) : (startIdx + stringsPerThread);

            auto task = [this, mark, &luckyNums, startIdx, endIdx]() {
                size_t cnt = 0;
                for (size_t j = startIdx; j < endIdx; ++j) {
                    if (map[j][luckyNums[j]-1] == mark) {
                        cnt++;
                    }
                }
                return cnt;
            };

            std::packaged_task<size_t()> packagedTask(task);
            futures.push_back(packagedTask.get_future());
            std::thread(std::move(packagedTask)).detach();
        }

        // Retrieve the data from the futures
        for (size_t i = 0; i < 4; ++i) {
            count += futures[i].get();
        }

        return count;
    }

    std::vector<int> MineSweeper::generateLuckyNumbers() const {
        std::vector<int> luckyNums(rows);
        bool satisfied = false;
        auto time = std::time(nullptr);
        std::srand(time); // use current time as seed for random generator
        while (!satisfied) {
            for (size_t n = 0; n < rows; ++n) {
                int x = rows + 1;
                while (x > rows) {
                    x = 1 + std::rand() / ((RAND_MAX + 1u) / rows);
                }
                luckyNums[n] = x;
            }
            // Ask user if they like the numbers
            char choice;
            std::cout << "\nGenerated numbers: ";
            for (int num : luckyNums) {
                std::cout << num << ' ';
            }
            std::cout << "\n\nDo you like these numbers? (y/n): ";
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                satisfied = true;
            }
            else if (choice == 'n' || choice == 'N') {
                // Generate new numbers
                continue;
            }
            else {
                std::cout << "Invalid choice. Please enter y or n." << std::endl;
            }
        }

        return luckyNums;
    }

    MineSweeper& MineSweeper::readFile(const char* filename) {
        std::fstream fin(filename);
        if (fin) {
            map = new std::string[rows];
            size_t idx = 0;
            while (fin) {
                getline(fin, map[idx]);
                idx++;
            }
            colSize = map[0].length();
        }
        else {
            throw std::string(filename) + " cannot be opened";
        }
        return *this;
    }

    void MineSweeper::generateRandomMap() {
        Utilities ut;
        auto numbers = ut.generateLuckyNumbers(rows);
        map = new std::string[rows]; 

        for (size_t i = 0; i < rows; i++) {
            map[i] = std::string(colSize, '-'); 
            map[i][numbers[i] - 1] = '*'; 
        }
    }

    void MineSweeper::setRowsCols(size_t num){
        rows = num;
        colSize = num;
    }

    size_t digForMine(std::vector<std::vector<size_t>> partition, std::vector<std::vector<int>> luckynums, char mark) {
        size_t cnt = 0;
        for (size_t i = 0; i < partition.size(); i++) {
            if (partition[i][i] == luckynums[i][i]) {
                cnt++;
            }
        }
        return cnt;
    }



}