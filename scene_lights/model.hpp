#pragma once 
#include "mesh.hpp"

#include <map>
#include <vector>

struct Model {
    std::vector<Mesh> meshes;
    std::map<std::string, MeshInstance> meshInstances;
};
