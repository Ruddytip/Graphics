#include "Render.hpp"
#include <cmath>
#include <iostream>

namespace RTT{
    Matrix XY(const double angle){
        Matrix out = {{cos(angle), -sin(angle), 0},
                      {sin(angle), cos(angle),  0},
                      {0,          0,           1}};
        return out;
    }
    Matrix YZ(const double angle){
        Matrix out = {{1, 0,          0          },
                      {0, cos(angle), -sin(angle)},
                      {0, sin(angle), cos(angle) }};
        return out;
    }
    Matrix XZ(const double angle){
        Matrix out = {{cos(angle), 0, -sin(angle)},
                      {0 ,         1, 0          },
                      {sin(angle), 0, cos(angle) }};
        return out;
    }
};

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
    for(unsigned int i = 0; i < (*model.getVerts()).size(); ++i){
        Matrix m(1, 3);
        m[0][0] = (*model.getVerts())[i].x;
        m[0][1] = (*model.getVerts())[i].y;
        m[0][2] = (*model.getVerts())[i].z;

        double angle = 45 * 3.1415 / 180;
        Matrix out = RTT::XZ(angle) * m;

        (*model.getVerts())[i].x = out[0][0];
        (*model.getVerts())[i].y = out[0][1];
        (*model.getVerts())[i].z = out[0][2];
    }

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

void Render::drawPerspectiveMesh(Canvas& image, Model& model, const double cof){

    for(unsigned int i = 0; i < (*model.getVerts()).size(); ++i){
        Matrix m(1, 3);
        m[0][0] = (*model.getVerts())[i].x;
        m[0][1] = (*model.getVerts())[i].y;
        m[0][2] = (*model.getVerts())[i].z;

        double angle = -20 * 3.1415 / 180;
        Matrix out = RTT::XZ(angle) * m;

        (*model.getVerts())[i].x = out[0][0];
        (*model.getVerts())[i].y = out[0][1];
        (*model.getVerts())[i].z = out[0][2];
    }

    // В 3D графике обычно используется матрица 4 на 4. А вектор представлен как R=(x,y,z,w)
    Matrix R(1, 4); R[0][0] = 0.0; R[0][1] = 0.0; R[0][2] = 1.0; R[0][3] = 1.0;
    // Где w=1 - вспомогательная велечина.
    // Проекционную матрицу умножаем на вектор R получаем Rp=(Xp,Yp,Zp) - спроектированный вектор.
    // Проекционная матрица может быть полученна различными способами. Часто применяют отрогональную и перспективную.
    // Обычно перспективная проекция задается следующими параметрами.
    // Fov- угол обзора камеры в играх выбирают 60°С 90°С 120°С.
    double fov = 60;
    // Aspect - соотношение сторон экрана x'/ y', обычно 4/3; 5/4; 16/9 просто берем разрешения экрана и делим ширину на высоту.
    double aspect = image.getWidth() / image.getHeight();
    // NearPlane -передняя плоскость ее Z координата
    double nearPlane = 0.0;
    // FarPlane - задняя плоскость ее Z координата.
    double farPlane = 1000.0;
    // Объекты будут рисоваться только те, которые находятся между задней и передней плоскостью.

    double h = 1.0 / tan(fov / 2.0);
    double w = aspect * h;
    double a = farPlane / (farPlane - nearPlane);
    double b = -nearPlane * farPlane / (farPlane - nearPlane);

    Matrix Perspect = {{h, 0, 0, 0},
                       {0, w, 0, 0},
                       {0, 0, a, b},
                       {0, 0, 1, 0}};

    // Если есть перспектива, то x_{new}=x_p/w_p, y_{new}=y_p/w_p, z_{new}=z_p/w_p
    // z - в дальнейшем используется в z буффере если нужно если ненужно просто отбрасываем
    // Дальше идут видовые преобразования . Преобразования координат полученных после применения проекционных преобразований нужно отмаштабировать и вывести на экран в видовое окно.

    // Экранные преобразование приведение проекционных координат к видовому окну.
    // Пусть окно имеет размер Width - ширина Height- высота
    // Left-левый край Top верхний крайн.

    // x,y имеют проекционные координаты -1..+1
    // Где (1,1) -верхний правый угол окна
    // Где (-1,-1) -нижний левый угол окна

    // xv = left + width  * (1 + xNew) / 2
    // yv = top  + height * (1 - yNew) / 2
    for (int i = 0; i < model.getFaces()->size(); ++i) {
        Face face = (*model.getFaces())[i];
        Vec3d arr[3];
        arr[0] = (*model.getVerts())[face.indexV.x];
        arr[1] = (*model.getVerts())[face.indexV.y];
        arr[2] = (*model.getVerts())[face.indexV.z];

        for (int j = 0; j < 3; j++) {
            Vec3d v0 = arr[j];
            Vec3d v1 = arr[(j + 1) % 3];

            Matrix v0_m(1, 4);
            v0_m[0][0] = v0.x;
            v0_m[0][1] = v0.y;
            v0_m[0][2] = v0.z;
            v0_m[0][3] = 1.0;
            Matrix v0_out = Perspect * v0_m;
            v0.x = v0_out[0][0];
            v0.y = v0_out[0][1];
            v0.z = v0_out[0][2];

            Matrix v1_m(1, 4);
            v1_m[0][0] = v1.x;
            v1_m[0][1] = v1.y;
            v1_m[0][2] = v1.z;
            v1_m[0][3] = 1.0;
            Matrix v1_out = Perspect * v1_m;
            v1.x = v1_out[0][0];
            v1.y = v1_out[0][1];
            v1.z = v1_out[0][2];

            int x0 = image.getWidth()  * ( v0.x) * cof + image.getWidth()  * 0.5;
            int y0 = image.getHeight() * (-v0.y) * cof + image.getHeight() * 0.5;
            int x1 = image.getWidth()  * ( v1.x) * cof + image.getWidth()  * 0.5;
            int y1 = image.getHeight() * (-v1.y) * cof + image.getHeight() * 0.5;
            line(x0, y0, x1, y1, image, model.GetColor());
        }
    }

}

Camera::Camera(const Vec3d _origin, const Vec3d _scale, const Vec3d _space):
Object(Vec3d(0.0, 0.0, 0.0), Vec3d(1.0, 1.0, 1.0), Vec3d(1.0, 1.0, 1.0)){}
void Camera::setOrigin(const Vec3d _origin){ Object::setOrigin(_origin);}
void Camera::setLookAt(const Vec3d _space){ Object::setSpace(_space); }