#pragma once
#include "BMP.hpp"
#include "Model.hpp"

class Render{
private:
    void line(int x0, int y0, int x1, int y1, Canvas &image, const Color color);
public:
    void drawIzometricMesh(Canvas& image, Model& model, const double cof);
};