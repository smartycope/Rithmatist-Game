#pragma once
#include <cassert>

// #include <GL/glew.h>
// #include <SDL2/SDL_opengl.h>

#include "Point.hpp"
#include "Color.hpp"

#include "Globals.hpp"

class Line{
private:
    int accuracy;                 // how close is the given line to what it's supposed to be?
    bool unidentified;
    Color lineColor;

    void addVertices(std::pair<float, float>);

protected:
    Point start;
    Point end;

public:
    std::vector<Point>* lineData;  // all the stuff in the middle //TODO this is protected when not debugging
    std::vector<float>* vertices;
    bool isFinished;

    Line(Point start = Point()): 
        start(start), 
        lineColor(Color()),
        accuracy(0),
        isFinished(false),
        lineData(new std::vector<Point>),
        vertices(new std::vector<float>)
        {};
    Line(Point start, Point end): 
        start(start), 
        end(end), 
        lineColor(Color()),
        accuracy(0),
        isFinished(true),
        lineData(new std::vector<Point>),
        vertices(new std::vector<float>)
        {};
    Line(Point start, Point end, std::vector<Point>* data): 
        start(start),
        end(end),
        lineColor(Color()),
        // lineData(new std::vector<Point>(data)),
        lineData(data),
        vertices(new std::vector<float>),
        accuracy(0),
        isFinished(true)
        {};
    ~Line();

    void draw();                   //! Depricated
    Line identifyLine(Line* line);
    void finish(Point end);
    void finish(Point end, const std::vector<Point>& data);
    int  getDataLen();
    std::vector<Point>* getData(); //! Depricated
    void erase();
    std::vector<float>* update(Color playersColor = Color());
    void init();
};