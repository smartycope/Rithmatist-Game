#pragma once
#include "Line.hpp"
#include "Point.hpp"


#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL.h>
#define GLEW_STATIC



class LineForbiddence:Line{
private:
    // float slope;
    Line optimal(/*optimal vector for a line*/);
public:
    LineForbiddence() {};
    // LineForbiddence(Point start = Point(), Point end = Point(), std::vector<Point> data): Line(start, end, data) {};
    void preDraw();
    void draw();
    void deleteVBOs();
    float getSlope();
};