#pragma once

#include <string>

#include "Color.hpp"
#include "Line.hpp"

#define DRAW_COLOR 0.989f, 0.989f, 0.989f, 0.989f

class Player{
private:
public:
    bool breached;
    Color lineColor;
    std::vector<Line> lines;
    std::string name;

    Player(): lineColor(Color(DRAW_COLOR)), breached(false), name("___") {};
    Player(std::string name): lineColor(Color(DRAW_COLOR)), breached(false), name(name) {};

   std::vector<float> getVertices();
};