#pragma once 
#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>

struct Model {
    Model(const char *fileName);

    void traverseScene(const aiNode *node, aiMatrix4x4 parentTransform);

    std::vector<Mesh> meshes;
    std::map<std::string, MeshInstance> meshInstances;
};

