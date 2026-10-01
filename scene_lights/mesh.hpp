#pragma once

#include "material.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <cstdint>
#include <string>

typedef struct VertexUntextured {
    glm::vec3 position;
    glm::vec3 normal;
} VertexUntextured;

typedef struct VertexTextured {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
} VertexTextured;

struct Mesh {
    const std::string name;
    size_t indexCnt;
    uint32_t materialIdx;
    bool hasTexture = false;
    //uint32_t textureId;
    uint32_t vao;
};

struct MeshInstance {
    uint32_t idx;
    glm::mat4 transform;
};
