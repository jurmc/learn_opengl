#include "camera.hpp"

#include <glm/glm.hpp>

glm::vec3 Camera::getTarget() const {
    glm::vec3 targetVec = glm::vec3(
            glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mYaw)),
            glm::sin(glm::radians(mPitch)),
            glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch)));
    glm::vec3 targetPos = mPos + targetVec;

    return targetPos;
}

