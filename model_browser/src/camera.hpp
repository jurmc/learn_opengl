#pragma once

#include <glm/glm.hpp>

class Camera {
    public:
        glm::vec3 getTarget() const;

    public:
        float mFov{glm::radians(45.0f)};
        glm::vec3 mPos{0.0f, 0.0f, 3.0f};
        float mYaw = -90.0f;  // degrees
        float mPitch = 0.0f;  // degrees
        float mRoll = 0.0f;   // degrees
};
