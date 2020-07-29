#pragma once

#include <iostream>
#include <any>
#include <iomanip>
// #include "Point.hpp"
#include <vector>
#include <string>
#define RAD2DEG 56.54866776;
#define verbose 4
#define TOO_MUCH 50

#define appendVector(main, append)                                        \
    switch(append.size()){                                                \
        case 0:                                                           \
            break;                                                        \
        case 1:                                                           \
            main.push_back(append[0]); break;                             \
        default:                                                          \
            main.insert(main.end(), append.begin(), append.end()); break; \
    }

#define logVal(var) std::cout << g::getDebugCount() << ": " << #var << " = " << var << std::endl;

// #define appendVector(main, append) \
//     for(auto iterator = append.begin(); iterator != append.end(); ++iterator) \
//         main.push_back(*iterator);

// #define appendVector(main, append) \
//     for(unsigned long notI = 0; notI < append.size(); ++notI) \
//         main.push_back(append[notI]);


/*
0: No debug info
1: 
2: 
3: 
4: 
5: All debug info
*/

// unsigned long debugCount = 0;

namespace g{

unsigned long getDebugCount();

void log(std::string message, unsigned int verbosity = verbose);

void printVector(const std::vector<float>& v, int itemsPerLine = -1, int spacing = 11);

void printVector(const std::vector<int>& v, int itemsPerLine = -1, int spacing = 11);

// void appendVector(const std::vector<)

// void printVector(const std::vector<Point>& v, int itemsPerLine = -1, int spacing = 11);
} // namespace g
