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
    int accuracy;                // how close is the given line to what it's supposed to be?
    bool unidentified;

public:
    Point start;
    Point end;
   std::vector<Point> lineData;     // all the stuff in the middle
    bool isFinished;
    // Color lineColor;

    Line(Point start = Point()): start(start), isFinished(false) {};
    Line(Point start, Point end): start(start), end(end), isFinished(true) {};
    Line(Point start, Point end, const std::vector<Point>& data): start(start), end(end), lineData(data), isFinished(true) {};
    // Line(vector<Point>* dataP): lineDataP(dataP) {};

    void draw();
    Line identifyLine(Line line);
    void finish(Point end);
    void finish(Point end, const std::vector<Point>& data);
    int  getDataLen();
    //std::vector<float> vertex(vector<Point>& data);
   std::vector<Point> getData();
    //std::vector<float
};