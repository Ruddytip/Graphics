#pragma once
#include <string>
#include <vector>
#include "Canvas.hpp"
#include "Geometry.hpp"

// Полигон (треугольник)
struct Face{
    Vec3ui indexV; // Индексы геометрических вершин
    Vec3ui indexU; // Индексы текстурных вершин
    Vec3ui indexN; // Индексы нормалей
};

class Object{
private:
    Vec3d origin; // Расположение центра координат
    Vec3d scale; // Локальные координаты
    Vec3d space; // Локальные углы
public:
    // 
    Object(const Vec3d _origin, const Vec3d _scale, const Vec3d _space);
    // 
    void setOrigin(const Vec3d _origin);
    // 
    void setScale(const Vec3d _scale);
    // 
    void setSpace(const Vec3d _space);
};

class Model: public Object{
private:
    std::string name; // Имя
    std::vector<Vec3d> verts; // Массив вершиных (геометрические координаты)
    std::vector<Vec2d> uv; // Массив текстурных координат
    std::vector<Vec3d> normals; // Массив нормалей
    Color color; // Цвет объекта
    Canvas texture; // Текстура
    Canvas normalMap; // Карта нормалей
    Canvas AOMap; // Карта затенения
    Canvas transparencyMap; // Карта прозрачности
    Canvas reflectionMap; // Карта отражения
    std::vector<Face> faces; // Полигоны (треугольники) из которых состоит объект
    std::vector<Model> models; // Подобъекты из которых состоит объект
public:
    Model();
    void setName(const std::string _name);
    void setOrigin(const Vec3d _origin);
    void setScale(const Vec3d _scale);
    void setSpace(const Vec3d _space);
    void setColor(const Color _color);
    void setTexture(const Canvas _texture);
    void setNormalMap(const Canvas _normalMap);
    void setAOMap(const Canvas _AOMap);
    void setTransparencyMap(const Canvas _transparencyMap);
    void setReflectionMap(const Canvas _reflectionMap);
    void addVert(const Vec3d _vert);
    void addUv(const Vec2d _uv);
    void addNormal(const Vec3d _normal);
    void addFace(const Face _face);
    void addModel(const Model _model);
    Color GetColor();
    std::vector<Vec3d>* getVerts();
    std::vector<Vec2d>* getUv();
    std::vector<Vec3d>* getNormals();
    std::vector<Face>* getFaces();
    std::vector<Model>* getModels();
};
