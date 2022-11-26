#include "Render.hpp"

void Render::line(int x0, int y0, int x1, int y1, Canvas& image, const Color color) {
    bool steep = false;
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1-x0;
    int dy = y1-y0;
    int derror2 = std::abs(dy)*2;
    int error2 = 0;
    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {
            image.setPixel(y, x, color);
        } else {
            image.setPixel(x, y, color);
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (y1>y0?1:-1);
            error2 -= dx*2;
        }
    }
}

void Render::drawIzometricMesh(Canvas& image, Model& model, const double cof){
    for (int i = 0; i < model.getFaces()->size(); ++i) {
        Face face = (*model.getFaces())[i];
        Vec3d arr[3];
        arr[0] = (*model.getVerts())[face.indexV.x];
        arr[1] = (*model.getVerts())[face.indexV.y];
        arr[2] = (*model.getVerts())[face.indexV.z];
        for (int j = 0; j < 3; j++) {
            Vec3d v0 = arr[j];
            Vec3d v1 = arr[(j + 1) % 3];
            int x0 = (v0.x + 1.) * image.getWidth() * cof;
            int y0 = (v0.y + 1.) * image.getHeight() * cof;
            int x1 = (v1.x + 1.) * image.getWidth() * cof;
            int y1 = (v1.y + 1.) * image.getHeight() * cof;
            line(x0, y0, x1, y1, image, model.GetColor());
        }
    }
}