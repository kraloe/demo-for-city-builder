#pragma once
#include <cmath>
inline void rotate_point(float cx,float cy,float angle, float& x,float& y){
    float s=std::sin(angle), c=std::cos(angle);
    x -= cx; y -= cy;
    float nx = x*c - y*s;
    float ny = x*s + y*c;
    x = nx + cx; y = ny + cy;
}
