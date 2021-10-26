#pragma once

template<typename T>
struct Vec2{
    T x, y;
    Vec2(T _x, T _y) : x(_x), y(_y) {};
};

template<typename T>
struct Vec3{
    T x, y, z;
    Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};
};

typedef Vec2<int> Vec2i;
typedef Vec2<double> Vec2d;
typedef Vec3<int> Vec3i;
typedef Vec3<double> Vec3d;
