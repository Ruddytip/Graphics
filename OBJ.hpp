#pragma once
#include <string>
#include "Model.hpp"

class OBJ{
private:
public:
    void downloadModel(const std::string& fileName, Model& model);
    void saveModel(const std::string& fileName, const Model& model) const;
};