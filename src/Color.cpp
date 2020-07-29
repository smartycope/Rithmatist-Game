#include "Color.hpp"

float Color::round(float var, int digits) {
    // 37.66666 * 100 =3766.66 
    // 3766.66 + .5 =3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    float value = int((var * (digits * 10) + .5));
    return float(value / (digits * 10));
}