#include "Point.hpp"

float Point::round(float var, int digits) { 
    // 37.66666 * 100 =3766.66 
    // 3766.66 + .5 =3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    float value = int((var * (digits * 10) + .5));
    return float(value / (digits * 10));
}

std::pair<float, float> Point::getVector(){
    // Point tmp(x, y);
    // tmp.convCenter();
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