#include "BMP.hpp"
#include "OBJ.hpp"
#include "Render.hpp"
#include "Matrix.hpp"
#include <iostream>

int main(){
    // const unsigned int w = 1000, h = 1000;
    // Model model;
    // OBJ file;
    // file.downloadModel("models/african_head/source/african_head.obj", model);
    // // file.downloadModel("models/tennyson/source/model.obj", model);
    // // file.downloadModel("models/orc/source/model.obj", model);
    
    // Canvas image(w, h, Color(0, 0, 0, 0));

    // Render Rout;
    // Rout.drawIzometricMesh(image, model, 0.5);

    // BMP out(image);
    // out.writeToFile("out.bmp");

    Matrix m(6);
    m[4][2] = 9;
    std::cout << m << std::endl;
    std::cout << !m << std::endl;

    return 0;
}