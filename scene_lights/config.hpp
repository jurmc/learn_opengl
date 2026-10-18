#pragma once

#include <glm/glm.hpp>

typedef struct LightSource {
    bool initialized = false;
    uint32_t vao;
    size_t indexCnt;
    glm::vec3 position;
    glm::mat4 transform;
    glm::vec3 color;
} LightSource;

typedef struct SceneConfig {
    LightSource lightSource;
} SceneConfig;
