#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include "MineSweeper.h"

int main(int argc, char** argv) {
    std::cout << "Command Line: " << argv[0];
    for (int i = 1; i < argc; i++)
        std::cout << " " << argv[i];
    std::cout << std::endl << std::endl;

    if (argc != 3) {
        std::cerr << std::endl << "***Incorrect number of arguments***" << std::endl;
        return 1;
    }

    try {
        stdd::MineSweeper tmap(argv[1]);

        auto time = std::time(nullptr);
        std::srand(time); // use current time as seed for random generator
        int random_value = std::rand();

        std::cout << "Press Enter to generate your lucky numbers...";
        std::cin.get(); // Wait for Enter key press

        std::cout << "Generating random numbers...\n";
        std::vector<int> luckyNums;
        std::cout << "Your lucky Numbers: ";
        for (int n = 0; n != tmap.size(); ++n) {
            int x = tmap.size() + 1;
            while (x > tmap.size())
                x = 1 + std::rand() / ((RAND_MAX + 1u) / tmap.size());
            luckyNums.push_back(x);
            std::cout << x << ' ';
        }
        std::cout << std::endl;

        std::cout << "***Finding mines on current Map***" << std::endl;
        size_t mineFound = tmap.findMine('*', luckyNums);
        std::cout << "You found " << mineFound << " mines!\n";
        tmap.display(std::cout);

    }
    catch (std::string& msg) {
        std::cout << msg << std::endl;
    }

    return 0;
}