#include "Point.hpp"

std::pair<float, float> Point::getVector(){
    Point tmp = this->convCenter();
    std::pair<float, float> tmp2(float(tmp.x) / (float(g::windowWidth) / 2.0f), (float(tmp.y) / (float(g::windowHeight) / 2.0f)) * -1);
    return tmp2;
}

void Point::print(){
    std::cout << x << ", " << y;
}

Point Point::convCenter(){
    Point tmp(float(this->x) - float(g::windowWidth) / 2.0f, float(this->y) - float(g::windowHeight) / 2.0f);
    return tmp;
}

Point Point::convTopLeft(){
    Point tmp(float(x) + float(g::windowWidth) / 2.0f, float(y) + float(g::windowHeight) / 2.0f);
    return tmp;
}

std::pair<float, float> Point::getUnnormalizedVector(){
    std::pair<float, float> tmp2(float(x), float(y) * -1);
    return tmp2;
}
