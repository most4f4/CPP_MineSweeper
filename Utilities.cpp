#include <cstdlib>
#include <ctime>
#include "Utilities.h"

namespace stdd {

	size_t Utilities::MainMenu(std::ostream& os)
	{
        std::cout << "******************************************\n"
            << "====== Welcome to MineSweeper Game! ======\n"
            << "******************************************\n\n";
        bool validNum = false;
        size_t numRows{};
        while (!validNum) {
            std::cout << "Select difficulty level : \n"
                << "1- Easy\n"
                << "2- Medium\n"
                << "3- Hard\n> ";
            // Get user's choice for difficulty level
            int choice;
            std::cin >> choice;

            switch (choice) {
            case 1:
                numRows = 6;
                validNum = true;
                break;
            case 2:
                numRows = 8;
                validNum = true;
                break;
            case 3:
                numRows = 10;
                validNum = true;
                break;
            default:
                std::cerr << "Invalid choice!\n\n";
                break;
            }
        };
        std::cout << std::endl;
        return numRows;
	}

    size_t Utilities::PlayType(std::ostream& os)
    {
        bool validNum = false;
        size_t choice;
        while (!validNum) {
            std::cout << "Please select your play type: \n"
                << "1- Predefined Map\n"
                << "2- Randomly Generated Map\n> ";

            std::cin >> choice;
            if (choice == 1 || choice == 2) {
                validNum = true;
            }
            else {
                std::cerr << "Invalid choice!\n\n";
            }
        }
        std::cout << std::endl;
        return choice;
    }

    std::vector<int> Utilities::generateLuckyNumbers(int num) {
        std::vector<int> luckyNums(num);
        auto time = std::time(nullptr);
        std::srand(time); // use current time as seed for random generator
        for (size_t n = 0; n < num; ++n) {
            int x = num + 1;
            while (x > num) {
                x = 1 + std::rand() / ((RAND_MAX + 1u) / num);
            }
            luckyNums[n] = x;
        }
        return luckyNums;
    }

}


