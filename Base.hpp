#ifndef __Base_hpp_2018_06_27_19_44
#define __Base_hpp_2018_06_27_19_44

#include <cmath>
#include <Hash.hpp>
#include <utility>

enum class Direction{
    NONE,NORTH, SOUTH, EAST, WEST
};

struct Vec2{
    int x,y;
    constexpr Vec2():x(0),y(0){}
    constexpr Vec2(int x,int y):x(x),y(y){}
    constexpr Vec2 operator+(const Vec2& v)const{
        return {x+v.x,y+v.y};
    }
    constexpr Vec2& operator+=(const Vec2& v){
        x+=v.x;
        y+=v.y;
        return *this;
    }
    constexpr Vec2 operator-(const Vec2& v)const{
        return {x-v.x,y-v.y};
    }
    constexpr Vec2& operator-=(const Vec2& v){
        x-=v.x;
        y-=v.y;
        return *this;
    }
    constexpr double magnetude()const{
        return sqrt(x*x+y*y);
    }
    constexpr double angle()const{
        return atan(double(x)/y);
    }
    constexpr static Vec2 fromMagnetudeDirection(double magnetude,double angle){
        return {int(magnetude*sin(angle)),int(magnetude*cos(angle))};
    }
    constexpr int32_t hashCode()const{
        return x*31+y;
    }

};
constexpr const Vec2 ZERO{0,0};

constexpr int32_t hashcode(const Vec2& v){
    return v.x*31+v.y;
}
constexpr int32_t hashcode(Vec2&& v){
    return v.x*31+v.y;
}

namespace std{
    template<> struct hash<Vec2>{
        constexpr hash()=default;
        constexpr size_t operator()(const Vec2& v){
            return hashcode(v);
        }
    };
};


#endif