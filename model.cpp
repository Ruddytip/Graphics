#include "model.hpp"
#include <fstream>
#include <iostream>

void Model::obj_parser(){
    std::ifstream in;
    in.open(path + "/model.obj", std::ifstream::in);
    if(in.fail()){
        std::cerr << "Can`t open file obj!\n";
        return;
    }

    in.close();
}

void Model::mtl_parser(){

}

Model::Model(std::string _str, Vec2i _size_screen) : verts(), objects(), size_screen(_size_screen), size(.0, .0, .0), pos(.0, .0, .0), rot(.0, .0, .0), path(_str){
    unsigned int size_buf = size_screen.x * size_screen.y;
    z_buffer = new double[size_buf];
    for(int i = 0; i < size_buf; ++i) z_buffer[i] = -std::numeric_limits<double>::max();
    obj_parser();
    mtl_parser();
}

Model::~Model(){
    delete[] z_buffer;
}

void Model::draw(HDC _hdc){

}

void Model::draw_isometric_mesh(HDC _hdc){

}