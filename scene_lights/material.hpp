#pragma once

#include "glm/glm.hpp"

enum class MaterialType {
    None,
    Texture,
    Color,
};

struct Material {
    MaterialType type{MaterialType::None};
    glm::vec4 diffuse;
    uint32_t textureId;
};
