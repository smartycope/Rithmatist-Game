#pragma once

#include <iostream>
#include <any>
#include <iomanip>
#include "Point.hpp"

using std::vector;

namespace g{

unsigned long debugCount = 0;
const int verbose = 4;
/*
0: No debug infob
1: 
2: 
3: 
4: 
5: All debug info
*/

void log(std::string message, unsigned int verbosity = verbose){
    if(verbosity <= verbose)
        std::cout << ++debugCount << ": " << message << std::endl;
}

void printVector(const vector<float>& v, int itemsPerLine = -1, int spacing = 10){
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

void printVector(const vector<int>& v, int itemsPerLine = -1, int spacing = 10){
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

void printVector(const vector<Point>& v, int itemsPerLine = -1, int spacing = 10){
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
} // namespace g