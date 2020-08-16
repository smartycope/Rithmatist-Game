#pragma once

#include "Globals.hpp"
#include "Line.hpp"

#include <vector>

class Geometry:public Line{
private:
    Line* line;

    // Guesses what type of line this Line is so we can test and see
    Type guessType();

    float getAccuracy(Line::Type bestGuess);

    float getAmplitude();
    float getwavelength();

    // Used for circle and maybe ellipse
    float getAverageRadius();
    float getAverageDeviation(std::vector<Point> opt);
    float getTotalDeviation(std::vector<Point> opt);
    // Finds the closest point in the list to what it's given
    std::pair<int, float> findClosestPoint(Point target, std::vector<Point> comparator);
    // Gets the points furthest from each other in the vector
    std::pair<int, int> findFurthestPoints();

    float getDist(Point a, Point b);
    float getSlope(Point a, Point b);
    float getAverage(const std::vector<int> &averagers);

public:
    Geometry():        line(nullptr) {}; // only use with generator functions
    Geometry(Line* l): line(l)       {};

    // These are used to manually create lines (that's why they're public)
    // Generate vectors filled with the points required to draw the "perfect" shape
    std::vector<Point> genOptCircle(Point center, float radius);
    std::vector<Point> genOptLine(Point start, Point end);
    std::vector<Point> genOptEllipse();
    std::vector<Point> genOptSine(Point start, float wavelength, float amplitude, float cycles = 2.0f);

    Type identify();
};