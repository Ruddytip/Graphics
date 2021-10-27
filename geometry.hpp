#pragma once
#include <vector>
#include "vec.hpp"

struct face{
    std::vector<int> id_v;
};

struct object{
    std::vector<int> id_f;
    std::string nameObject;
};