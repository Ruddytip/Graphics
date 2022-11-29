#pragma once
#include "BMP.hpp"
#include "Model.hpp"
#include "Matrix.hpp"

// Матрицы поворотов
namespace RTT{
    Matrix XY(const double angle);
    Matrix YZ(const double angle);
    Matrix XZ(const double angle);
};

class Render{
private:
    void line(int x0, int y0, int x1, int y1, Canvas &image, const Color color);
public:
    void drawIzometricMesh(Canvas& image, Model& model, const double cof);
    void drawPerspectiveMesh(Canvas& image, Model& model, const double cof);
};

class Camera : Object{
private:
public:
    Camera(const Vec3d _origin, const Vec3d _scale, const Vec3d _space);
    void setOrigin(const Vec3d _origin);
    void setLookAt(const Vec3d _space);
};