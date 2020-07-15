#pragma once
#include "Line.hpp"
#include "Point.hpp"

#define radius (diameter / 2)

class LineWarding:Line{
private:
    Point north, south, east, west; // the furthest according points of the circle
    float diameter;
public:
    LineWarding(): Line() {};
};