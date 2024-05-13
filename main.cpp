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
#include "Utilities.h"


int main(int argc, char** argv) {
    std::cout << "Command Line: " << argv[0];
    for (int i = 1; i < argc; i++)
        std::cout << " " << argv[i];
    std::cout << std::endl << std::endl;

    if (argc != 4) {
        std::cerr << std::endl << "***Incorrect number of arguments***" << std::endl;
        return 1;
    }

    try {
        stdd::Utilities ut;
        stdd::MineSweeper tmap;
        auto numRows = ut.MainMenu(std::cout);
        tmap.setRowsCols(numRows);
        auto choice = ut.PlayType(std::cout);
        switch (numRows) {
        case 6:
            if (choice == 1) tmap.readFile(argv[1]);
            else tmap.generateRandomMap();
            break;
        case 8:
            if (choice == 1) tmap.readFile(argv[2]);
            else tmap.generateRandomMap();
            break;
        case 10:
            if (choice == 1) tmap.readFile(argv[3]);
            else tmap.generateRandomMap();
            break;
        default:
            break;
        }

        std::cout << "Press Enter to generate your lucky numbers...";
        std::cin.get(); // Wait for Enter key press

        auto luckyNums = tmap.generateLuckyNumbers();
        std::cout << "\n***Finding mines on current Map***" << std::endl;
        size_t mineFound = tmap.findMine('*', luckyNums);
        std::cout << "\nYou found " << mineFound << " Mines!\n\n";
        std::cout << "Your numbers were: ";
        for (const auto& num : luckyNums) {
            std::cout << num << ' ';
        }
        std::cout << std::endl;
        std::cout << "\nMAP: \n\n";
        tmap.display(std::cout);       
    }
    catch (std::string& msg) {
        std::cout << msg << std::endl;
    }
    return 0;
}
