#pragma once

#include "Globals.hpp"
#include "Line.hpp"

#include <vector>

class Geometry:public Line{
private:
    Line* line;

    // Guesses what type of line this Line is so we can test and see
    Type guessType();

    double getAccuracy(Line::Type bestGuess);

    double getAmplitude();
    double getwavelength();

    // Used for circle and maybe ellipse
    double getAverageRadius();
    double getAverageDeviation(std::vector<Point> opt);
    // Exactly the same as getAverageDeviation(), but punishes distance from the line exponentially
    double getExponentialAverageDeviation(std::vector<Point> opt);
    double getTotalDeviation(std::vector<Point> opt);
    std::pair<int, double> getGreatestDeviation(std::vector<Point> opt);
    // Finds the closest point in the list to what it's given
    std::pair<int, double> findClosestPoint(Point target, std::vector<Point> comparator);
    // Gets the points furthest from each other in the vector
    std::pair<int, int> findFurthestPoints();
    double getLineLength();

    double getDist(Point a, Point b);
    double getSlope(Point a, Point b);
    double getAverage(const std::vector<int> &averagers);
    bool  isCloseEnough(Point a, Point b, double threshold);
    bool  isCloseEnough(double a, double b, double threshold);
    double clampToPercentage(double value, double perfect, double acceptableCuttoff, double failureCutoff);

public:
    Geometry():        line(nullptr) {}; // only use with generator functions
    Geometry(Line* l): line(l)       {};

    // These are used to manually create lines (that's why they're public)
    // Generate vectors filled with the points required to draw the "perfect" shape
    std::vector<Point> genOptCircle(Point center, double radius, bool ordered = true); //todo This is false when not debugging
    std::vector<Point> genOptLine(Point start, Point end);
    std::vector<Point> genOptEllipse();
    std::vector<Point> genOptSine(Point start, double wavelength, double amplitude, double cycles = 2.0f);

    Type identify();
};