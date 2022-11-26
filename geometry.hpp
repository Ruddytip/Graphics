#pragma once
#include <cmath>

template<typename T>
struct Vec2{
    T x, y;
    Vec2<T>(): x(0), y(0){}
    Vec2<T>(const T _x, const T _y): x(_x), y(_y){}
    Vec2<T> operator+(const T _data)   { x+=_data; y+=_data; return *this;}
    Vec2<T> operator+(const Vec2<T> _V){ x+=_V.x;  y+=_V.y;  return *this;};
    Vec2<T> operator-(const T _data)   { x-=_data; y-=_data; return *this;}
    Vec2<T> operator-(const Vec2<T> _V){ x-=_V.x;  y-=_V.y;  return *this;};
    Vec2<T> operator/(const T _data)   { x/=_data; y/=_data; return *this;}
    // Длина вектора
    double operator~(){ return sqrt(x * x + y * y); }
    // Нормализует вектор
    Vec2<T> operator!(){ return ((*this) / ~(*this)); }
    // Умножение вектора на число
    Vec2<T> operator*(const T _data){ x*=_data; y*=_data; return *this;}
    // Скалярное произведение векторов
    double operator*(const Vec2<T> _V){ return (x * _V.x + y * _V.y); }
    // Угол между векторами
    double operator^(const Vec2<T> _V){ return ((*this) * _V) / (~(*this) * ~_V); }
};

template<typename T>
struct Vec3{
    T x, y, z;
    Vec3<T>(): x(0), y(0), z(0){}
    Vec3<T>(const T _x, const T _y, const T _z): x(_x), y(_y), z(_z){}
    Vec3<T> operator+(const T _data)   { x+=_data; y+=_data; z+=_data; return *this;}
    Vec3<T> operator+(const Vec3<T> _V){ x+=_V.x;  y+=_V.y;  z+=_V.z;  return *this;};
    Vec3<T> operator-(const T _data)   { x-=_data; y-=_data; z-=_data; return *this;}
    Vec3<T> operator-(const Vec3<T> _V){ x-=_V.x;  y-=_V.y;  z-=_V.z;  return *this;};
    Vec3<T> operator/(const T _data)   { x/=_data; y/=_data; z/=_data; return *this;}
    // Длина вектора
    double operator~(){ return sqrt(x * x + y * y + z * z); }
    // Нормализует вектор
    Vec3<T> operator!(){ return ((*this) / ~(*this)); }
    // Умножение вектора на число
    Vec3<T> operator*(const T _data){ x*=_data; y*=_data; z*=_data; return *this;}
    // Скалярное произведение векторов
    double operator*(const Vec3<T> _V){ return (x * _V.x + y * _V.y + z * _V.z); }
    // Угол между векторами
    double operator^(const Vec3<T> _V){ return ((*this) * _V) / (~(*this) * ~_V); }
    // Векторное произведение векторов
    Vec3<T> operator%(const Vec3 _V){ 
        return Vec3<T>(y * _V.z - z * _V.y, z * _V.x - x * _V.z, x * _V.y - y * _V.x);
    }
};

typedef Vec2<double> Vec2d;
typedef Vec2<unsigned int> Vec2ui;
typedef Vec3<double> Vec3d;
typedef Vec3<unsigned int> Vec3ui;