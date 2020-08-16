#include "Geometry.hpp"
#include "Globals.hpp"

#include <math.h>
#include <string>
#include <vector>

#define LINE_FORBIDDENCE_PRECISION 10.f

// Generate vectors filled with the points required to draw the "perfect" shape
std::vector<Point> Geometry::genOptCircle(Point center, float radius){
    std::vector<Point> opt;
    return opt;
}

std::vector<Point> Geometry::genOptLine(Point start, Point end){
    std::vector<Point> opt;

    /* Native line drawing algorithm - doesn't currently work
    int dx = end.x - start.x;
    int dy = end.y - start.y;

    bool positiveSlope = start.x > end.x;

    for (int x = start.x; positiveSlope ? (x >= end.x) : (x <= end.x); positiveSlope ? --x : ++x){
        int y = ((start.y + dy) * (x - start.x)) / dx;
        _log(std::to_string(x) + ", " + std::to_string(y));
        opt.push_back(Point(x, y));
    }
    */

    // https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm) 

    float x, y, dx, dy, step;
    int i;

    float x1 = start.x, y1 = start.y, x2 = end.x, y2 = end.y;

    dx = (x2 - x1);
    dy = (y2 - y1);
    if (abs(dx) >= abs(dy))
        step = abs(dx);
    else
        step = abs(dy);
    dx = dx / step;
    dy = dy / step;
    x = x1;
    y = y1;
    i = 1;
    while (i <= step) {
        // putpixel(x, y, 5);
        opt.push_back(Point(x, y));
        x = x + dx;
        y = y + dy;
        i = i + 1;
    }

    return opt;
}

std::vector<Point> Geometry::genOptEllipse(){
    std::vector<Point> opt;
    return opt;
}

std::vector<Point> Geometry::genOptSine(Point start, float wavelength, float amplitude, float cycles){
    std::vector<Point> opt;
    return opt;
}

float Geometry::getAccuracy(Line::Type bestGuess){
    switch(bestGuess){
        case LINE_DOT:
        case LINE_UNKNOWN:
        case LINE_MAKING:
        case LINE_REVOCATION:
        case LINE_VIGOR:
        case LINE_WARDING:
        case LINE_FORBIDDENCE:
        {
            std::vector<Point> optLine = genOptLine(line->start, line->end);
            return 100.f - getAverageDeviation(optLine) 
                         -(getTotalDeviation(optLine) / LINE_FORBIDDENCE_PRECISION);

            // return (getAverageDeviation(optLine) * LINE_FORBIDDENCE_PRECISION) - getTotalDeviation(optLine);
        }
        default:
            break;
    }
}

// Finds the closest point in the list to what it's given
std::pair<int, float> Geometry::findClosestPoint(Point target, std::vector<Point> comparator){
    int index = 0;
    float finalDist = 10000, current;

    for (int i = 0; i < comparator.size(); ++i){
        current = getDist(target, comparator[i]);
        if (current < finalDist){
            finalDist = current;
            index = i;
        }
    }
    // logVal(finalDist)
    return std::pair<int, float>(index, finalDist);
}
// Gets the points furthest from each other in the vector
std::pair<int, int> Geometry::findFurthestPoints(){
    int a, b;
    return std::pair<int, int>(a, b);
}
// Self explanitory (used for circle and ellipse)
float Geometry::getAverageRadius(){
    std::vector<int> radii;

    return getAverage(radii);
}

float Geometry::getAverageDeviation(std::vector<Point> opt){
    int i = 0;
    float netDist = 0.f;
    for(; i < line->lineData->size(); ++i){
        netDist += findClosestPoint((*line->lineData)[i], opt).second;
    }
    // logVal(this->line->lineData->size())
    // logVal(i)
    // logVal(netDist)
    logVal(netDist / i)
    return netDist / i; // The average distance of the closest points
}

float Geometry::getTotalDeviation(std::vector<Point> opt){
    float netDist = 0.f;
    for(int i = 0; i < line->lineData->size(); ++i){
        netDist += findClosestPoint((*line->lineData)[i], opt).second;
    }
    logVal(netDist)
    return netDist; // The average distance of the closest points
}

// Guesses what type of line this Line is
Line::Type Geometry::guessType(){
    
    return LINE_FORBIDDENCE;
}

Line::Type Geometry::identify(){
    Type guessedType = guessType();

    float acc = getAccuracy(guessedType);

    line->lineType = guessedType;
    line->accuracy = acc;

    if (acc < 50.f)
        return LINE_UNKNOWN;
    else
        return guessedType;
}

float Geometry::getAmplitude(){
    
    return 0;
}

float Geometry::getwavelength(){

    return 0;
}

float Geometry::getAverage(const std::vector<int> &averagers){
    int total = 0;
    for (auto i: averagers)
        total += i;
    return total / averagers.size();
}

float Geometry::getDist(Point a, Point b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

float Geometry::getSlope(Point a, Point b){
    return (b.y - a.y) / (b.x - a.x);
}