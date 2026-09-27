#pragma once

#include "material.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <cstdint>
#include <string>

struct Mesh {
    const std::string name;
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    uint32_t materialIdx;
    uint32_t vao;
};

struct MeshInstance {
    uint32_t idx;
    glm::mat4 transform;
};
