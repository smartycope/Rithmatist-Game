#pragma once

// #include "Gui.hpp"
#include <iostream>
#include <array>
#include <algorithm>

// using std::vector;
using std::array;

// Defualt origin is top-left corner of the window!!!

class Point{
private:
    // Gui gui;
    int width  = 485;
    int height = 300;

    float round(float var, int digits = 1);

public:
    int x, y;

    Point(): x(0), y(0) {};
    Point(int x, int y): x(x), y(y) {};

    void print();
    array<float, 2> getVector();
    Point convCenter();
    Point convTopLeft();
};