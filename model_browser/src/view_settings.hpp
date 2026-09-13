#pragma once

#include "imgui.h"

#include <glm/glm.hpp>

enum class DisplayMethod { Wireframe, Solid };

struct ViewSettings {
    DisplayMethod mDisplayMethod = DisplayMethod::Solid;
    ImVec4 mLightColor{1.0f, 1.0f, 1.0f, 1.0f};
    float mLightStrength = 1.0f;

    // TODO: this will be real camera properties, once we have camera
    float mFov{glm::radians(45.0f)};
    glm::vec3 mRotation{0.0f, 0.0f, 0.0f};
    glm::vec3 mCameraPos{0.0f, 0.0f, -3.0f};  // TODO: once we have camera direction needs to be reversed
};

