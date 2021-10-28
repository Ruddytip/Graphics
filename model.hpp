#pragma once
#include <windows.h>
#include <string>
#include "geometry.hpp"

class Model{
private:
    std::vector<Vec3d> verts;
    std::vector<face> faces;
    std::vector<object> objects;
    Vec2i size_screen;
    Vec3d size;
    Vec3d pos;
    Vec3d rot;
    Vec3d scale;
    Vec3d min, max;
    double* z_buffer;
    std::string path;
    std::string name_model;
    void obj_parser();
    void mtl_parser();
    void line(HDC _hdc, Vec2i _p0, Vec2i _p1, COLORREF* color);
public:
    Model(std::string _str, Vec2i _size_screen);
    ~Model();
    void draw(HDC _hdc);
    void draw_isometric_mesh(HDC _hdc);
};