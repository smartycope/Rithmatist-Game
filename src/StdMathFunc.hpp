#include "Point.hpp"
#include "Line.hpp"

// These all assume y is inverted (i.e. origin = top left corner)


template <class T>
T getMin (T a, T b);

template <class T>
T getMax (T a, T b);

// Get the distance between 2 points
double getDist(Point a, Point b);

// Get the slope between 2 points 
//  (gets the angle between point b, and an imaginary line drawn right along the x axis of point a, counterclockwise)
double getSlope(Point a, Point b, bool giveRadians = true);

template <class T>
T getAverage(const std::vector<T>& averagers);
Point getAverage(const std::vector<Point>& averagers);

template <class T>
bool isCloseEnough(T a, T b, T threshold);
bool isCloseEnough(Point a, Point b, double threshold);

int getLeftmostPoint(std::vector<Point> data);
int getRightmostPoint(std::vector<Point> data);
int getTopmostPoint(std::vector<Point> data);
int getBottommostPoint(std::vector<Point> data);

Point adjPoint(Point pt);

// Compare 2 vectors of points and get how much on average they're different
double getAverageDeviation(std::vector<Point> opt, std::vector<Point> subOpt);

// Exactly the same as getAverageDeviation(), but punishes distance from the line exponentially
double getExponentialAverageDeviation(std::vector<Point> opt, std::vector<Point> subOpt, double exp);

// Same as getAverageDeviation(), but totals the distance instead of averaging it
double getTotalDeviation(std::vector<Point> opt, std::vector<Point> subOpt);

// Returns the index of the point in subOpt that deviates the most
std::pair<int, double> getGreatestDeviation(std::vector<Point> opt, std::vector<Point> subOpt);

// Gets the points furthest from each other in the given vector
std::pair<int, int> findFurthestPoints(std::vector<Point> data);

// Gets the point in coparator that is furthest from target
std::pair<int, double> findFurthestPoint(Point target, std::vector<Point> comparator);

// Opposite of findFurthestPoint()
std::pair<int, double> findClosestPoint(Point target, std::vector<Point> comparator);

// Calculates the length of the given line (even if it's curvy)
double getLineLength(const Line& lucy);

// Rotates any line to be straight along the x axis
void rotateStraight(Line& lucy, bool isSine = true);

void rotate(Line& lucy, double degrees, bool radians = true);