#include "model.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

void Model::obj_parser(){
    std::ifstream in;
    in.open(path + "/model.obj", std::ifstream::in);
    if(in.fail()){
        std::cerr << "Can`t open file obj!\n";
        return;
    }

    std::string line;
    std::string trash;
    while(!in.eof()){
        std::getline(in, line);
        std::stringstream iss(line);

        if(!line.compare(0, 1, "#")){
            continue;
        }
        else if(!line.compare(0, 2, "v ")){
            iss >> trash; std::string data[3];
            for(int i = 0; i < 3; ++i) iss >> data[i];
            Vec3d _vert(std::stod(data[0]), std::stod(data[1]), std::stod(data[2]));
            verts.push_back(_vert);
        }else if(!line.compare(0, 2, "f ")){
            face _face;
            std::string data[4]; iss >> trash;
            for(int i = 0; i < 4; ++i) {
                iss >> data[i];
                if(!data[i].empty()){
                    data[i].erase(data[i].find('/'));
                }
            }
            for(int i = 0; i < 3; ++i) _face.id_v.push_back(stoi(data[i]) - 1);
            faces.push_back(_face);
            if(!data[3].empty()){
                face _another_face;
                _another_face.id_v.push_back(stoi(data[0]) - 1);
                _another_face.id_v.push_back(stoi(data[2]) - 1);
                _another_face.id_v.push_back(stoi(data[3]) - 1);
                faces.push_back(_another_face);
            }
        }else if(!line.compare(0, 2, "o ")){
            iss >> trash; iss >> trash;
            object _object;
            _object.nameObject = trash;
            objects.push_back(_object);
        }

    }

    in.close();
}

void Model::mtl_parser(){

}

void Model::line(HDC _hdc, Vec2i _p0, Vec2i _p1, COLORREF* color){
    bool steep = false;
    if (std::abs(_p0.x - _p1.x) < std::abs(_p0.y - _p1.y)){
        std::swap(_p0.x, _p0.y);
        std::swap(_p1.x, _p1.y);
        steep = true;
    }
    if (_p0.x > _p1.x) {
        std::swap(_p0, _p1);
        // std::swap(x0, x1);
        // std::swap(y0, y1);
    }
    int dx = _p1.x - _p0.x;
    int dy = _p1.y - _p0.y;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = _p0.y;
    for (int x = _p0.x; x <= _p1.x; x++) {
        if (steep) {
            SetPixel(_hdc, y, x, *color);
        } else {
            SetPixel(_hdc, x, y, *color);
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (_p1.y > _p0.y ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

Model::Model(std::string _str, Vec2i _size_screen) : verts(), faces(), objects(), size_screen(_size_screen), size(.0, .0, .0), pos(.0, .0, .0), rot(.0, .0, .0), path(_str){
    unsigned int size_buf = size_screen.x * size_screen.y;
    z_buffer = new double[size_buf];
    for(unsigned int i = 0; i < size_buf; ++i) z_buffer[i] = -std::numeric_limits<double>::max();
    obj_parser();
    mtl_parser();
}

Model::~Model(){
    delete[] z_buffer;
}

void Model::draw(HDC _hdc){
    draw_isometric_mesh(_hdc);
}

void Model::draw_isometric_mesh(HDC _hdc){
    for(unsigned int id_f = 0; id_f < faces.size(); ++id_f){
        for(unsigned int id_v = 0; id_v < verts.size(); ++id_v){
            
        }
    }
}