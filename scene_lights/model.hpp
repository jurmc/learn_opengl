#pragma once 

#include "mesh.hpp"
#include "material.hpp"
#include "config.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>
#include <cstdint>

struct Model {
    Model(const char *fileName, SceneConfig& config);

    void traverseScene(const aiNode *node, aiMatrix4x4 parentTransform);

    SceneConfig& config;
    std::vector<Mesh> meshes;
    std::vector<Material> materials;
    std::map<std::string, MeshInstance> meshInstances;
};

