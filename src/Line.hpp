#pragma once
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "Point.hpp"
#include "Color.hpp"

// #include "Debug.hpp"
// Debug d;

using std::vector;
using std::array;

class Line{
private:
    int accuracy;                // how close is the given line to what it's supposed to be?
    bool unidentified;

public:
    Point start;
    Point end;
    vector<Point> lineData;     // all the stuff in the middle
    bool isFinished;
    // Color lineColor;

    Line(Point start = Point()): start(start), isFinished(false) {};
    Line(Point start, Point end): start(start), end(end), isFinished(true) {};
    Line(Point start, Point end, const vector<Point>& data): start(start), end(end), lineData(data), isFinished(true) {};
    // Line(vector<Point>* dataP): lineDataP(dataP) {};

    void draw();
    Line identifyLine(Line line);
    void finish(Point end);
    void finish(Point end, const vector<Point>& data);
    int  getDataLen();
    // vector<float> vertex(vector<Point>& data);
    vector<Point> getData();
    // vector<float
};