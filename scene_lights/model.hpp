#pragma once 

#include "mesh.hpp"
#include "material.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <map>
#include <vector>
#include <cstdint>

typedef struct LightSource {
    bool initialized = false;
    uint32_t vao;
    size_t indexCnt;
    glm::vec3 position;
    glm::mat4 transform;
} LightSource;

struct Model {
    Model(const char *fileName);

    void traverseScene(const aiNode *node, aiMatrix4x4 parentTransform);

    std::vector<Mesh> meshes;
    std::vector<Material> materials;
    std::map<std::string, MeshInstance> meshInstances;

    LightSource lightSource;
};

