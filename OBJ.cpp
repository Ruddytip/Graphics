#include "OBJ.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

void OBJ::downloadModel(const std::string& fileName, Model& model){
    std::ifstream fin(fileName, std::ios_base::binary);
    if (!fin.is_open()) return;
    while(!fin.eof()){
        std::string in(""), buff("");
        std::getline(fin, in);
        std::stringstream iss(in.c_str());
        if (!in.compare(0, 2, "v ")){
            iss >> buff;
            Vec3d vert;
            iss >> buff; vert.x = std::stod(buff);
            iss >> buff; vert.y = std::stod(buff);
            iss >> buff; vert.z = std::stod(buff);
            model.addVert(vert);
        } else if (!in.compare(0, 3, "vt ")){
            iss >> buff;
            Vec2d uv;
            iss >> buff; uv.x = std::stod(buff);
            iss >> buff; uv.y = std::stod(buff);
            model.addUv(uv);
        } else if (!in.compare(0, 3, "vn ")){
            iss >> buff;
            Vec3d normal;
            iss >> buff; normal.x = std::stod(buff);
            iss >> buff; normal.y = std::stod(buff);
            iss >> buff; normal.z = std::stod(buff);
            model.addNormal(normal);
        } else if (!in.compare(0, 2, "f ")){
            iss >> buff;
            std::string buffX(""), buffY(""), buffZ("");
            Face face;
            face.indexV = Vec3ui(0, 0, 0);
            face.indexU = Vec3ui(0, 0, 0);
            face.indexN = Vec3ui(0, 0, 0);
            iss >> buffX >> buffY >> buffZ; 
            int count = std::count(buff.begin(), buff.end(), '/');
            if(count == 0){
                face.indexV.x = std::stoi(buffX) - 1;
                face.indexV.y = std::stoi(buffY) - 1;
                face.indexV.z = std::stoi(buffZ) - 1;
            } else if(count == 1){
                Vec3ui pos(buffX.find('/'), buffY.find('/'), buffZ.find('/'));
                face.indexV.x = std::stoi(buffX.substr(0, pos.x)) - 1;
                face.indexV.y = std::stoi(buffY.substr(0, pos.y)) - 1;
                face.indexV.z = std::stoi(buffZ.substr(0, pos.z)) - 1;
                face.indexN.x = std::stoi(buffX.substr(pos.x + 2, buffX.length() - 1)) - 1;
                face.indexN.y = std::stoi(buffY.substr(pos.y + 2, buffY.length() - 1)) - 1;
                face.indexN.z = std::stoi(buffZ.substr(pos.z + 2, buffZ.length() - 1)) - 1;
            } else if(count == 2){
                Vec3ui pos1(buffX.find('/'), buffY.find('/'), buffZ.find('/'));
                Vec3ui pos2(buffX.find_last_of('/'), buffY.find_last_of('/'), buffZ.find_last_of('/'));
                face.indexV.x = std::stoi(buffX.substr(0, pos1.x)) - 1;
                face.indexV.y = std::stoi(buffY.substr(0, pos1.y)) - 1;
                face.indexV.z = std::stoi(buffZ.substr(0, pos1.z)) - 1;
                if((pos2.x - pos1.x) > 1) face.indexU.x = std::stoi(buffX.substr(pos1.x + 2, pos2.x)) - 1;
                if((pos2.y - pos1.y) > 1) face.indexU.y = std::stoi(buffY.substr(pos1.y + 2, pos2.y)) - 1;
                if((pos2.z - pos1.z) > 1) face.indexU.z = std::stoi(buffZ.substr(pos1.z + 2, pos2.z)) - 1;
                face.indexN.x = std::stoi(buffX.substr(pos2.x + 2, buffX.length() - 1)) - 1;
                face.indexN.y = std::stoi(buffY.substr(pos2.y + 2, buffY.length() - 1)) - 1;
                face.indexN.z = std::stoi(buffZ.substr(pos2.z + 2, buffZ.length() - 1)) - 1;
            }
            model.addFace(face);
        }
    }
    fin.close();
}

void OBJ::saveModel(const std::string& fileName, const Model& model) const{

}