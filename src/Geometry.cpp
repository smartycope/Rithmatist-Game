#include "Geometry.hpp"
#include "Globals.hpp"

#include <math.h>
#include <string>
#include <vector>

#define LINE_FORBIDDENCE_PRECISION 100.f
#define PRECISION 2

// This is to be able to have a reversed for-based range loop
template <typename T>
struct reversion_wrapper { T& iterable; };
template <typename T>
auto begin (reversion_wrapper<T> w) { return std::rbegin(w.iterable); }
template <typename T>
auto end (reversion_wrapper<T> w) { return std::rend(w.iterable); }
template <typename T>
reversion_wrapper<T> reverse (T&& iterable) { return { iterable }; }


// Generate vectors filled with the points required to draw the "perfect" shape
// The ordered flag toggles whether to order the points for nice drawing or not
std::vector<Point> Geometry::genOptCircle(Point center, double radius, bool ordered){
    std::vector<Point> opt;
    // main, Bottom Right, Bottom Left, Top Left: starts at the Top Right
    std::vector<Point> optTR1, optBR1, optBL1, optTL1, optTR2, optBR2, optBL2, optTL2;

    // Mid-Point Circle Drawing Algorithm -- Works, but draws the points out of order, making OpenGL draw them funny
    int x = radius, y = 0; 
    
    opt.push_back(Point(center.x + radius, center.y));
    if (ordered) // To make OpenGL draw the starting gap
       opt.push_back(Point(center.x + radius, center.y + 1));

    // When radius is zero only a single point will be printed 
    if (radius > 0){
        // opt.push_back(Point(x + center.x, -y + center.y));
        // opt.push_back(Point(y + center.x, x + center.y));
        // opt.push_back(Point(-y + center.x, x + center.y));
    }
    
    // Initialising the value of P
    int P = 1 - radius; 
    while (x > y){
        y++; 
        
        // Mid-point is inside or on the perimeter 
        if (P <= 0) 
            P = P + 2*y + 1; 
        // Mid-point is outside the perimeter 
        else{
            x--; 
            P = P + 2*y - 2*x + 1; 
        } 
        
        // All the perimeter points have already been printed 
        if (x < y) 
            break; 
        
        // Printing the generated point and its reflection
        // in the other octants after translation
        if (ordered){
            optTR1.push_back(Point(x + center.x, y + center.y));
            optTL1.push_back(Point(-x + center.x, y + center.y));
            optBR1.push_back(Point(x + center.x, -y + center.y));
            optBL1.push_back(Point(-x + center.x, -y + center.y));
        }
        else{
            opt.push_back(Point(x + center.x, y + center.y));
            opt.push_back(Point(-x + center.x, y + center.y));
            opt.push_back(Point(x + center.x, -y + center.y));
            opt.push_back(Point(-x + center.x, -y + center.y));
        }
        
        // If the generated point is on the line x = y then the perimeter points have already been printed
        if (x != y){
            if (ordered){
                optTR2.push_back(Point(y + center.x, x + center.y));
                optTL2.push_back(Point(-y + center.x, x + center.y));
                optBR2.push_back(Point(y + center.x, -x + center.y));
                optBL2.push_back(Point(-y + center.x, -x + center.y));
            }
            else{
                opt.push_back(Point(y + center.x, x + center.y));
                opt.push_back(Point(-y + center.x, x + center.y));
                opt.push_back(Point(y + center.x, -x + center.y));
                opt.push_back(Point(-y + center.x, -x + center.y));
            }
        } 
    }

    if (ordered){
        // Now assemble all those points properly
        // This ordering works, but it looks messed up. 
        //  I think I messed up the octant naming or something.
        for(auto it: optBR1)
            opt.push_back(it);
        for(auto it: reverse(optBR2))
            opt.push_back(it);
        for(auto it: optBL2)
            opt.push_back(it);
        for(auto it: reverse(optBL1))
            opt.push_back(it);

        opt.push_back(Point(center.x - radius, center.y));

        for(auto it: optTL1)
            opt.push_back(it);
        for(auto it: reverse(optTL2))
            opt.push_back(it);
        for(auto it: optTR2)
            opt.push_back(it);
        for(auto it: reverse(optTR1))
            opt.push_back(it);
    }
    else
        opt.push_back(Point(center.x - radius, center.y));

    if (ordered)
       opt.push_back(Point(center.x + radius, center.y - 1));

    // opt.push_back(Point(center.x + radius, center.y));

    /*
        errors between octants:
        TL1/TR1 and TL1/TL2

    */


    /*
       8        1               TR 1
           xxx                              
    7   x       x   2           TR 2
      x           x
      x           x
      x           x
    6   x       x   3           BR 1
           xxx
       5         4              BR 2 
    */

    /* Bresenham’s Algorithm -- Works, same problem
    int x = 0, y = radius; 
    int d = 3 - 2 * radius; 

    opt.push_back(Point(center.x + x, center.y + y)); 
    opt.push_back(Point(center.x - x, center.y + y)); 
    opt.push_back(Point(center.x + x, center.y - y)); 
    opt.push_back(Point(center.x - x, center.y - y)); 
    opt.push_back(Point(center.x + y, center.y + x)); 
    opt.push_back(Point(center.x - y, center.y + x)); 
    opt.push_back(Point(center.x + y, center.y - x)); 
    opt.push_back(Point(center.x - y, center.y - x));

    while (y >= x){
        // for each pixel we will draw all eight pixels 
        x++; 
        
        // check for decision parameter and correspondingly update d, x, y 
        if (d > 0){
            y--;  
            d = d + 4 * (x - y) + 10; 
        } 
        else
            d = d + 4 * x + 6; 

        opt.push_back(Point(center.x + x, center.y + y)); 
           ^
        opt.push_back(Point(center.x + x, center.y - y)); 
        opt.push_back(Point(center.x - x, center.y - y)); 
        opt.push_back(Point(center.x + y, center.y + x)); 
        opt.push_back(Point(center.x - y, center.y + x)); 
        opt.push_back(Point(center.x + y, center.y - x)); 
        opt.push_back(Point(center.x - y, center.y - x));
    }
    */
    
    /* Organize the points to be in order
    std::vector<Point> organizedOpt;
    /
           xxx
        x       x
      x           x
      x           x
      x           x
        x       x
           xxx
           ^
       start here
    /

    // Get the bottommost point
    assert(opt.size());
    Point bottomLeft;
    for(auto it: opt)
        if(it.y > bottomLeft.y)
            if(it.x < bottomLeft.x)
                bottomLeft = it;

    organizedOpt.push_back(bottomLeft);
    */

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

    double x, y, dx, dy, step;
    int i;

    double x1 = start.x, y1 = start.y, x2 = end.x, y2 = end.y;

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

std::vector<Point> Geometry::genOptSine(Point start, double wavelength, double amplitude, double cycles){
    std::vector<Point> opt;
    return opt;
}

double Geometry::getAccuracy(Line::Type bestGuess){
    switch(bestGuess){
        case LINE_DOT:
        case LINE_UNKNOWN:
        case LINE_MAKING:
        case LINE_REVOCATION:
        case LINE_VIGOR:
        case LINE_WARDING:
        case LINE_FORBIDDENCE:
        {   // getAverageDeviation() here can be approximated with getDist(start, end) / getLineLength().
            std::vector<Point> optLine = genOptLine(line->start, line->end);
            // return LINE_FORBIDDENCE_PRECISION - getAverageDeviation(optLine) * LINE_FORBIDDENCE_PRECISION / 10;

            // logVal(getExponentialAverageDeviation(optLine))
            // logVal(getGreatestDeviation(optLine).second)
            // logVal(((getExponentialAverageDeviation(optLine) * -1) - getGreatestDeviation(optLine).second) * -1)

            double answer = 100 - getExponentialAverageDeviation(optLine) - (getGreatestDeviation(optLine).second * 2);

            return answer < 0 ? 0 : answer; // If it's negative, just say 0. 
        }
        default:
            break;
    }
}

// Finds the closest point in the list to what it's given
std::pair<int, double> Geometry::findClosestPoint(Point target, std::vector<Point> comparator){
    int index = 0;
    double finalDist = 10000, current;

    for (int i = 0; i < comparator.size(); ++i){
        current = getDist(target, comparator[i]);
        if (current < finalDist){
            finalDist = current;
            index = i;
        }
    }
    // logVal(finalDist)
    return std::pair<int, double>(index, finalDist);
}
// Gets the points furthest from each other in the vector
std::pair<int, int> Geometry::findFurthestPoints(){
    int a, b;
    return std::pair<int, int>(a, b);
}
// Self explanitory (used for circle and ellipse)
double Geometry::getAverageRadius(){
    std::vector<int> radii;

    return getAverage(radii);
}

double Geometry::getAverageDeviation(std::vector<Point> opt){
    int i = 0;
    double netDist = 0.f;
    for(; i < line->lineData->size(); ++i){
        netDist += fabs(findClosestPoint((*line->lineData)[i], opt).second);
    }
    // logVal(this->line->lineData->size())
    // logVal(i)
    // logVal(netDist)
    // logVal(netDist / i)
    return netDist / i; // The average distance of the closest points
}
// Exactly the same as getAverageDeviation(), but punishes distance from the line exponentially
double Geometry::getExponentialAverageDeviation(std::vector<Point> opt){
    int i = 0;
    double netDist = 0.f;
    for(; i < line->lineData->size(); ++i){
        netDist += pow(fabs(findClosestPoint((*line->lineData)[i], opt).second), PRECISION);
    }
    // logVal(this->line->lineData->size())
    // logVal(i)
    // logVal(netDist)
    // logVal(netDist / i)
    return netDist / i; // The average distance of the closest points
}

double Geometry::getTotalDeviation(std::vector<Point> opt){
    double netDist = 0.f;
    for(int i = 0; i < line->lineData->size(); ++i){
        netDist += findClosestPoint((*line->lineData)[i], opt).second;
    }
    // logVal(netDist)
    return netDist;
}

std::pair<int, double> Geometry::getGreatestDeviation(std::vector<Point> opt){
    double currentDist = 0.f, finalDist = 0.f;
    int index = 0;

    for(int i = 0; i < line->lineData->size(); ++i){
        currentDist = findClosestPoint((*line->lineData)[i], opt).second;
        if (currentDist > finalDist){
            finalDist = currentDist;
            index = i;
        }
    }

    return std::pair<int, double>(index, finalDist);
}

// Guesses what type of line this Line is
Line::Type Geometry::guessType(){

    return LINE_FORBIDDENCE; //! For debugging

    assert(line->isFinished and not line->isNull());
    if (line->lineData->size() == 1)
        return LINE_DOT;

    else if (getDist(line->start, line->end) < getLineLength() / 8) // 8 is arbitrary
        return LINE_WARDING;

    // The length of the line of a sine wave is approx. sqrt(pow(amp, 2) + pow(wav / 4, 2))
    else if (getDist(line->start, line->end) < getLineLength() / 1.5) // 1.5 is arbitrary)
        return LINE_VIGOR;

    else if (isCloseEnough(getDist(line->start, line->end) / getLineLength(), 1.f, .3f))
        return LINE_FORBIDDENCE;

    else if (false)
        return LINE_REVOCATION;

    else if (false)
        return LINE_MAKING;

    else 
        return LINE_UNKNOWN;
}

Line::Type Geometry::identify(){
    Type guessedType = guessType();

    double acc = getAccuracy(guessedType);

    line->lineType = guessedType;
    line->accuracy = acc;

    // logVal(getDist(line->start, line->end) / getLineLength())

    if (acc < 50.f)
        return LINE_UNKNOWN;
    else
        return guessedType;
}

double Geometry::getAmplitude(){
    
    return 0;
}

double Geometry::getwavelength(){

    return 0;
}

double Geometry::getLineLength(){
    double total = 0.f;

    for (int i = 1; i < line->lineData->size(); ++i)
        total += getDist((*line->lineData)[i], (*line->lineData)[i - 1]);

    return total + 1;
}

double Geometry::getAverage(const std::vector<int> &averagers){
    int total = 0;
    for (auto i: averagers)
        total += i;
    return total / averagers.size();
}

double Geometry::getDist(Point a, Point b){
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    // return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double Geometry::getSlope(Point a, Point b){
    return (b.y - a.y) / (b.x - a.x);
}

bool Geometry::isCloseEnough(Point a, Point b, double threshold){
    if (fabs(getDist(a, b)) < threshold)
        return true;
    else
        return false;
}

bool Geometry::isCloseEnough(double a, double b, double threshold){
    if (fabs(a - b) < threshold)
        return true;
    else 
        return false;
}

double Geometry::clampToPercentage(double value, double perfect, double acceptableCutoff, double failureCutoff){

    return 6.;
}