#pragma once

#include <iostream>
#include <any>
#include <iomanip>
#include "Point.hpp"

// using std::vector;

/*
0: No debug infob
1: 
2: 
3: 
4: 
5: All debug info
*/

static unsigned int debugCount = 0;
const static int verbose = 4;

class Debug{
public:
    Debug() {};

    void logger(std::string message, unsigned int verbosity = verbose){
        if(verbosity <= verbose)
            std::cout << ++debugCount << ": " << message << std::endl;
    }

    void printVector(const std::vector<float>& v, int itemsPerLine = -1, int spacing = 10){
        std::cout << "\n";
        int count = 1;
        for (auto i: v){
            if ((count % itemsPerLine) or itemsPerLine == -1){
                std::cout << std::setw(spacing) << i << ", ";
                ++count;
            }
            else{
                std::cout << std::setw(spacing) << i << "\n";
                ++count;
            }
        }
        std::cout << "\n";
    }

    void printVector(const std::vector<int>& v, int itemsPerLine = -1, int spacing = 10){
        std::cout << "\n";
        int count = 1;
        for (auto i: v){
            if ((count % itemsPerLine) or itemsPerLine == -1){
                std::cout << std::setw(spacing) << i << ", ";
                ++count;
            }
            else{
                std::cout << std::setw(spacing) << i << "\n";
                ++count;
            }
        }
        std::cout << "\n";
    }

    void printVector(const std::vector<Point>& v, int itemsPerLine = -1, int spacing = 10){
        std::cout << "\n";
        int count = 1;
        for (auto i: v){
            if ((count % itemsPerLine) or itemsPerLine == -1){
                std::cout << '(' << i.x << ", " << i.y << "), ";
                ++count;
            }
            else{
                std::cout << '(' << i.x << ", " << i.y << ")\n";
                ++count;
            }
        }
        std::cout << "\n";
    }
};