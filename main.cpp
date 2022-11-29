#include "BMP.hpp"
#include "OBJ.hpp"
#include "Render.hpp"

int main(){
    const unsigned int w = 1000, h = 1000;
    Model model;
    OBJ file;
    file.downloadModel("models/african_head/source/african_head.obj", model);
    // file.downloadModel("models/tennyson/source/model.obj", model);
    // file.downloadModel("models/orc/source/model.obj", model);
    
    Canvas image(w, h, Color(0, 0, 0, 0));

    Render Rout;
    // Rout.drawIzometricMesh(image, model, 0.5);
    Rout.drawPerspectiveMesh(image, model, 3.0);

    BMP out(image);
    out.writeToFile("out.bmp");
    return 0;
}