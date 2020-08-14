#pragma once

#include "Globals.hpp"

namespace g{ extern unsigned int windowWidth, windowHeight; }

//* Defualt origin is top-left corner of the window!!!

class Point{
private:
public:
    int x, y;

    Point():
        x(-1), 
        y(-1) 
        {};
    Point(int x, int y): 
        x(x), 
        y(y) 
        {};

    void print();
    std::pair<float, float> getVector();
    std::pair<float, float> getUnnormalizedVector();
    Point convCenter();
    Point convTopLeft();
};