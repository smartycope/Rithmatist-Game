#pragma once
#include <cassert>

// #include <GL/glew.h>
// #include <SDL2/SDL_opengl.h>

#include "Point.hpp"
#include "Color.hpp"

class Line{
public:
    enum Type{
            LINE_FORBIDDENCE,
            LINE_VIGOR,
            LINE_WARDING,
            LINE_MAKING,
            LINE_REVOCATION,
            LINE_DOT,
            LINE_UNKNOWN
        } lineType;

private:
    Color lineColor;

    void addVertices(std::pair<float, float>);

public:
    //todo figure out why these can't be protected like they should be
    Point start;
    Point end;
    float accuracy;                //? Between 0% and 100%

    std::vector<Point>* lineData;  //  All the stuff in the middle
    std::vector<float>* vertices;
    bool isFinished;

    Line(Point start = Point()): 
        start(start), 
        lineColor(Color()),
        accuracy(-1.f),
        isFinished(false),
        lineType(LINE_UNKNOWN),
        lineData(new std::vector<Point>),
        vertices(new std::vector<float>)
        {};
    Line(Point start, Point end): 
        start(start), 
        end(end), 
        lineColor(Color()),
        accuracy(-1.f),
        isFinished(true),
        lineType(LINE_UNKNOWN),
        lineData(new std::vector<Point>),
        vertices(new std::vector<float>)
        {};
    Line(Point start, Point end, std::vector<Point> data): 
        start(start),
        end(end),
        lineColor(Color()),
        // lineData(new std::vector<Point>(data)),
        lineData(new std::vector<Point>(data)),
        vertices(new std::vector<float>),
        accuracy(-1.f),
        lineType(LINE_UNKNOWN),
        isFinished(true)
        {};
    ~Line();

    void draw();                   //! Depricated
    Type identifyLine();
    void finish(Point end, bool identify = true);
    void finish(Point end, const std::vector<Point> data, bool identify = true);
    int  getDataLen();
    std::vector<Point>* getData(); //! Depricated
    void erase();
    std::vector<float>* update(Color playersColor = Color(), bool isDot = false);
    void init();
    bool isNull();
    void append(Point where);
    void printAcc();
};