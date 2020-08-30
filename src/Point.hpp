#pragma once

#include "Globals.hpp"

namespace g{ extern unsigned int windowWidth, windowHeight; }

//* Defualt origin is top-left corner of the window!!!

class Point{
private:
public:
    int x, y;
    bool isNull;

    Point():
        x(0), 
        y(0),
        isNull(true) 
        {};
    Point(int x, int y): 
        x(x), 
        y(y),
        isNull(false)
        {};

    void print(std::string name = "");
    std::pair<float, float> getVector();
    std::pair<float, float> getUnnormalizedVector();
    Point convCenter();
    Point convTopLeft();

    bool operator==(const Point& r);
    bool operator!=(const Point& r);
};