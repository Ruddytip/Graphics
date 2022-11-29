#include "Model.hpp"

Object::Object(const Vec3d _origin, const Vec3d _scale, const Vec3d _space):
origin(_origin), scale(_scale), space(_space){}
void Object::setOrigin(const Vec3d _origin){ origin = _origin; }
void Object::setScale(const Vec3d _scale){ scale = _scale; }
void Object::setSpace(const Vec3d _space){ space = _space; }

Model::Model(): Object(Vec3d(.0, .0, .0), Vec3d(1.0, 1.0, 1.0), Vec3d(1.0, 1.0, 1.0)){
    setName("None");
    setColor(Color(255, 255, 255, 255));
    texture.clear(Color(255, 255, 255, 255));
    normalMap.clear(Color(255, 255, 255, 255));
    AOMap.clear(Color(255, 255, 255, 255));
    transparencyMap.clear(Color(255, 255, 255, 255));
    reflectionMap.clear(Color(255, 255, 255, 255));
}

void Model::setName(const std::string _name){ name = _name; }
void Model::setColor(const Color _color){ color = _color; }
void Model::setTexture(const Canvas _texture){ texture = _texture; }
void Model::setNormalMap(const Canvas _normalMap){ normalMap = _normalMap; }
void Model::setAOMap(const Canvas _AOMap){ AOMap = _AOMap;}
void Model::setTransparencyMap(const Canvas _transparencyMap){ transparencyMap = _transparencyMap;}
void Model::setReflectionMap(const Canvas _reflectionMap){ reflectionMap = _reflectionMap; }
void Model::addVert(const Vec3d _vert){ verts.push_back(_vert); }
void Model::addUv(const Vec2d _uv){ uv.push_back(_uv); }
void Model::addNormal(const Vec3d _normal){ normals.push_back(_normal); }
void Model::addFace(const Face _face){ faces.push_back(_face); }
void Model::addModel(const Model _object){ models.push_back(_object); }

Color Model::GetColor(){ return color; }
std::vector<Vec3d>* Model::getVerts(){ return &verts; }
std::vector<Vec2d>* Model::getUv(){ return &uv; }
std::vector<Vec3d>* Model::getNormals(){ return &normals; }
std::vector<Face>* Model::getFaces(){ return &faces; }
std::vector<Model>* Model::getModels(){ return &models; }
