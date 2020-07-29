#pragma once
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "Point.hpp"
#include "Color.hpp"

#include "Globals.hpp"

// using std::vector;
// using std::array;

class Line{
private:
    int accuracy;                 // how close is the given line to what it's supposed to be?
    bool unidentified;

public:
    Point start;
    Point end;
    std::vector<Point> lineData;  // all the stuff in the middle
    std::vector<float> vertices;
    bool isFinished;
    Color lineColor;

    Line(Point start = Point()): 
        start(start), 
        lineColor(Color()),
        accuracy(0),
        isFinished(false) {};
    Line(Point start, Point end): 
        start(start), 
        end(end), 
        lineColor(Color()),
        accuracy(0),
        isFinished(true) {};
    Line(Point start, Point end, const std::vector<Point>& data): 
        start(start), 
        end(end), 
        lineColor(Color()),
        lineData(data), 
        accuracy(0),
        isFinished(true) 
        {};

    void draw();
    Line identifyLine(Line* line);
    void finish(Point end);
    void finish(Point end, const std::vector<Point>& data);
    int  getDataLen();
    std::vector<Point> getData();
    void erase();
    std::vector<float> update(Color playersColor = Color());
};