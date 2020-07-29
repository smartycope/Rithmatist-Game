#pragma once

#include <string>

#include "Color.hpp"
#include "Line.hpp"
#include "Globals.hpp"

#define DRAW_COLOR 0.989f, 0.989f, 0.989f, 0.989f // just a distinct almost white for debugging purposes

class Player{
private:
    unsigned long numLines;

public:
    bool breached;
    Color drawColor;
    std::vector<Line> lines;
    std::vector<float> vertices;
    std::string name;

    Player(): 
        drawColor(Color(DRAW_COLOR)),
        breached(false), 
        name("___"), 
        numLines(0) 
        { init(); };
    Player(std::string name): 
        drawColor(Color(DRAW_COLOR)), 
        breached(false), 
        name(name), 
        numLines(0) 
        { init(); };

    std::vector<float> update();
    void init();
};