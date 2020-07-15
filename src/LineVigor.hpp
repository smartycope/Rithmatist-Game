#pragma once
#include "Line.hpp"
#include "Point.hpp"

class LineVigor:Line{
private:
public:
    LineVigor():Line() {};
    void draw();
    void shoot();
};