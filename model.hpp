#pragma once
#include "geometry.hpp"
#include <windows.h>
#include <string>
#include <vector>

class Model{
private:
    std::vector<Vec3d> verts;
    std::vector<object> objects;
    Vec2i size_screen;
    Vec3d size;
    Vec3d pos;
    Vec3d rot;
    double* z_buffer;
    std::string path;
    std::string name_model;
    void obj_parser();
    void mtl_parser();
public:
    Model(std::string _str, Vec2i _size_screen);
    ~Model();
    void draw(HDC _hdc);
    void draw_isometric_mesh(HDC _hdc);
};