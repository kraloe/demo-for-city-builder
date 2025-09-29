#pragma once
namespace Math {
struct vec2 {
    float x, y;
    vec2():x(0),y(0){} vec2(float X,float Y):x(X),y(Y){}
    vec2 operator+(const vec2& o) const { return vec2{x+o.x,y+o.y}; }
    vec2 operator-(const vec2& o) const { return vec2{x-o.x,y-o.y}; }
    vec2 operator*(float s) const { return vec2{x*s,y*s}; }
    vec2 operator/(float s) const { return vec2{x/s,y/s}; }
    vec2& operator+=(const vec2& o){ x+=o.x; y+=o.y; return *this; }
    vec2& operator-=(const vec2& o){ x-=o.x; y-=o.y; return *this; }
    vec2& operator*=(float s){ x*=s; y*=s; return *this; }
    vec2& operator/=(float s){ x/=s; y/=s; return *this; }
};
inline vec2 operator*(float s,const vec2& v){ return v*s; }
}
