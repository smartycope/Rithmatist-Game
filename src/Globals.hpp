#pragma once

#include <iostream>
#include <any>
#include <iomanip>
#include "Point.hpp"

using std::vector;

#define RAD2DEG 56.54866776;
#define verbose 4

/*
0: No debug infob
1: 
2: 
3: 
4: 
5: All debug info
*/

// unsigned long debugCount = 0;

namespace g{

void log(std::string message, unsigned int verbosity = verbose);

void printVector(const vector<float>& v, int itemsPerLine = -1, int spacing = 10);

void printVector(const vector<int>& v, int itemsPerLine = -1, int spacing = 10);

void printVector(const vector<Point>& v, int itemsPerLine = -1, int spacing = 10);
} // namespace g