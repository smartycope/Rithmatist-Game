#include "Geometry.hpp"
#include "Globals.hpp"

#include <math.h>
#include <string>
#include <vector>

#define LINE_FORBIDDENCE_PRECISION 100.f
// In getExponentialAvergeDeviation(), use this value to punish distace
#define DISTANCE_PENALTY_EXPONENT 2
// How many radius samples are taken (the greater the number, the more accurate, but slower it's going to be)
//  Put line->lineData->size() for max accuracy
#define MAX_RADIUS_SAMPLES line->lineData->size()
// Defines how many points forward or backward to check when assuming the circle's radius based on it's size
//  Used in efficent getAverageRadius()
#define OFFSET_CHECK_DISTANCE 10
// Defines the step of the slow way of calculating getFurthestPoints() (smaller is slower, but more accurate)
#define FIND_RADIUS_SLOW_EFFICENCY 1


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

std::vector<Point> Geometry::genOptSine(Point start, Point end, double wavelength, double amplitude, double cycles, bool niceLooking){
    std::vector<Point> opt;

    /**************** Formula of a Sine Wave *****************
    * @p A amplitude
    * @p f cycles
    * @p t time
    * @p shift phase shift
    *
    ** y(t) = A * sin(2 * PI * f * t + shift)
    *                         or...
    ** y(time) = amplitude * sin(2 * PI * cycles * time + phaseShift)
    **********************************************************/

    


/* 
    Vector p1 = new PVector(10,10);
    PVector p2 = new PVector(100,100);

    float gFreq = 2; // frequency
    float gAmp = 50; // amplitude in pixels


    void sineTo(PVector p1, PVector p2, float freq, float amp){
    float d = PVector.dist(p1,p2);
    float a = atan2(p2.y-p1.y,p2.x-p1.x);
        translate(p1.x,p1.y);
        rotate(a);
        beginShape();
        for (float i = 0; i <= d; i += 1) {
            vertex(i,sin(i*TWO_PI*freq/d)*amp);
        }
 */

    // This should NOT have been this difficult to figure out.

    // Create the actuall sine wave
    double x, y;
    double verticalShift = start.y, phaseShift = 7.;

    // for(x = start.x; x < (wavelength * cycles) + start.x; ++x){
    //     // y = amplitude * sin(2 * M_PI * (cycles / wavelength) * (x - start.x)) + start.y;
    //     y = amplitude * sin(((2 * M_PI) * (x + phaseShift)) / wavelength) + verticalShift;
    //     opt.push_back(Point(x, y));
    // }

    start.convCenter();
    end.convCenter();

    // Then change the angle of that sine wave
    double v = atan2(end.y - start.y, end.x - start.x);
    for(x = start.x; x < (wavelength * cycles) + start.x; ++x){
        y = amplitude * sin(((2 * M_PI) * (x + phaseShift)) / wavelength) + verticalShift;
        int newY = x *  cos(v)  + y * sin(v);
        int newX = x * -sin(v)  + y * cos(v);
        opt.push_back(Point(newX, newY));
    }


    // Because that only generate one point per x, draw lines between the points for comparing
    //  (actually looks slightly worse when drawn with OpenGL this way)
    if (not niceLooking){
        std::vector<Point> tmpOpt = opt;
        opt.clear();
        assert(tmpOpt.size() > 2);
        for(auto it = tmpOpt.begin() + 1; it < tmpOpt.end(); ++it){
            // opt.push_back(*(it - 1));
            std::vector<Point> tmp = genOptLine(*it, *(it - 1));
            appendVector(opt, tmp);
            // opt.push_back(*it);
        }
    }

    /* supposed to draw a sine wave between 2 points
    float v = atan2(end.y - start.y, end.x - start.x);
    for(int i = start.x; i < (wavelength * cycles) + start.x; ++i){
        int y = amplitude * sin(2 * M_PI * (cycles / wavelength) * (i - start.x) + 0) + start.y;
        // sin(i / waveStretcher) * waveMultiplier;
        // int y = sin(i / wavelength) * amplitude;
        int rotatedY = i * cos(v)  + y * sin(v);
        int x = i * -sin(v) + y * cos(v);
        Point addMe;
        opt.push_back(addMe.convTopLeft());
    }
    */

    // float v = atan2(y2 - y1, x2 - x1);
    // for(blabla){
    //     calculate sinPosY from i
    //     newSinPosY =    i*Cos(v)  + sinPosY*Sin(v);
    //     sinPosX =    i*-Sin(v) + sinPosY*Cos(v));
    //     add offset
    //     render
    // }



    /* Aaaaaalmost works, but not quite, something's off...
    cycles /= 2;
    for(int x = start.x; x < (wavelength * cycles) + start.x; ++x)
        opt.push_back(Point(x, amplitude * sin(2 * M_PI * (cycles / wavelength) * (x - start.x) + 0) + start.y));
    */

    /*
    double angle = 0.0;
    for(int x = start.x; x < (wavelength * cycles) + start.x; ++x){
        opt.push_back(Point(x, int(amplitude * sin(angle) + start.y)));
        angle += (2 * M_PI) / wavelength;
    }
    */

    // for (int x = 0; x < wavelength; ++x){
    //     auto y[wavelength] = amplitude * sin (2 * M_PI * (cycles / NUM_POINTS) * wavelength + 0);//  + ZERO_OFFSET;
    //                                                       ^^^ f = 15 cycles / NUM_POINTS = 0.15 Hz
    // }
    // loop from y[0] to y[wav]



    /* Some algorithm I found from TI that apparently they put in their graphing caclulators
    int x = 0;
    const short A = (1.975/2 * 32768); // (1.975/2 * 32768) = 0x7e66 -- this was origionally a short
    short y[3] = {0, 0x1209, 0};       // (0.1409 * 32768)  = 0x1209 -- this was origionally a short
    for(int i = 0; i < 40; i++){
        y[0] = (((A * y[1]) >> 15) + ((A * y[1]) >> 15)) - y[2];
        y[2] = y[1]; // y2 <–– y1
        y[1] = y[0]; // y1 <–– y0
        // output = y[0];
        opt.push_back(Point(x, y[0]));
        ++x;
    }
    */


    return opt;
}

double Geometry::getAccuracy(Line::Type bestGuess){
    switch(bestGuess){
        case LINE_DOT:
        case LINE_UNKNOWN:
        case LINE_MAKING:
        case LINE_REVOCATION:
        case LINE_VIGOR:
        {
            // std::vector<Point> optSine = genOptSine(line->start, 6., 6.);
            return NAN; // Fun note: breaking here instead of returning gives you an "Illegal instruction" error            
        }
        case LINE_WARDING:
        {
            double radius = getAverageRadius(false);
            Point  center = getCenter(radius);

            std::vector<Point> optCircle = genOptCircle(center, radius, false);

            double answer = 100 - getAverageDeviation(optCircle) - (getGreatestDeviation(optCircle).second * 2);

            return answer < 0 ? 0 : answer; // If it's negative, just say 0.
        }
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
    // I'm just going to assume it's at least vaugely a circle shape
    int a, b, i = 0;

    for (; i < line->lineData->size(); i += FIND_RADIUS_SLOW_EFFICENCY){

    }

    return std::pair<int, int>(a, b);
}
// Finds the furthest point in the list to what it's given
std::pair<int, double> Geometry::findFurthestPoint(Point target, std::vector<Point> comparator){
    int index = 0;
    double finalDist = 0, current;

    for (int i = 0; i < comparator.size(); ++i){
        current = getDist(target, comparator[i]);
        if (current > finalDist){
            finalDist = current;
            index = i;
        }
    }
    // logVal(finalDist)
    return std::pair<int, double>(index, finalDist);
}

double Geometry::getAverageRadius(bool efficent){
    std::vector<double> radii;
    int samples = MAX_RADIUS_SAMPLES;

    // The smarter way of doing things
    if (efficent){
        _log("Effeciently calculating radius...");
        auto sampler = line->lineData->begin();
        auto antiSampler = line->lineData->begin() + (lineData->size() / 2);

        while (samples){
            double finalDist = getDist(*sampler, *antiSampler);

            if (getDist(*sampler, *antiSampler) == finalDist)
                break;
            else if (getDist(*sampler, *(antiSampler + 1)) > finalDist)
                while(getDist(*sampler, *(++antiSampler)) > finalDist) { }
            else if (getDist(*sampler, *(antiSampler + 1)) > finalDist)
                while(getDist(*sampler, *(--antiSampler)) > finalDist) { }

            radii.push_back(getDist(*sampler, *antiSampler) / 2);

            --samples;
        }
    }
    // The easy way of doing things
    else{
        _log("Ineffeciently calculating radius...");
        for(auto it = line->lineData->begin(); it < line->lineData->end(); it += (line->lineData->size() / MAX_RADIUS_SAMPLES))
            radii.push_back(findFurthestPoint(*it, *line->lineData).second / 2);
    }

    return getAverage(radii);
}

Point Geometry::getCenter(double radius){
    Point rightmost  = (*line->lineData)[getRightmostPoint()];
    Point leftmost   = (*line->lineData)[getLeftmostPoint()];
    Point topmost    = (*line->lineData)[getTopmostPoint()];
    Point bottommost = (*line->lineData)[getBottommostPoint()];
    Point rightSays (rightmost.x - radius, rightmost.y);
    Point leftSays  (leftmost.x  + radius, leftmost.y );
    Point topSays   (topmost.x   , topmost.y    + radius);
    Point bottomSays(bottommost.x, bottommost.y - radius);

    std::vector<Point> centers = {rightSays, leftSays, topSays, bottomSays};
    Point avg = getAverage(centers);
    return avg;
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
        netDist += pow(fabs(findClosestPoint((*line->lineData)[i], opt).second), DISTANCE_PENALTY_EXPONENT);
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

    // return LINE_FORBIDDENCE; //! For debugging

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

double Geometry::getAverage(const std::vector<double>& averagers){
    double total = 0;
    for (auto i: averagers)
        total += i;
    return total / averagers.size();
}

Point Geometry::getAverage(const std::vector<Point>& averagers){
    Point total;
    for (auto i: averagers){
        total.x += i.x;
        total.y += i.y;
    }
    return Point(total.x / averagers.size(), total.y / averagers.size());
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

int Geometry::getLeftmostPoint(){
    int smallestX = 10000, index;
    for(int i = 0; i < line->lineData->size(); ++i){
        if ((*line->lineData)[i].x < smallestX){
            smallestX = (*line->lineData)[i].x;
            index = i;
        }
    }
    return index;
}

int Geometry::getRightmostPoint(){
    int largestX = 0, index;
    for(int i = 0; i < line->lineData->size(); ++i){
        if ((*line->lineData)[i].x > largestX){
            largestX = (*line->lineData)[i].x;
            index = i;
        }
    }
    return index;
}

int Geometry::getTopmostPoint(){
    int smallestY = 10000, index;
    for(int i = 0; i < line->lineData->size(); ++i){
        if ((*line->lineData)[i].y < smallestY){
            smallestY = (*line->lineData)[i].y;
            index = i;
        }
    }
    return index;
}

int Geometry::getBottommostPoint(){
    int largestY = 0, index;
    for(int i = 0; i < line->lineData->size(); ++i){
        if ((*line->lineData)[i].y > largestY){
            largestY = (*line->lineData)[i].y;
            index = i;
        }
    }
    return index;
}

double Geometry::clampToPercentage(double value, double perfect, double acceptableCutoff, double failureCutoff){

    return 6.;
}