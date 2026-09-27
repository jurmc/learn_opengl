#include <glm/glm.hpp>
#include <glm/ext.hpp>

typedef struct Camera {
    glm::vec3 pos{5.0f, 5.0f, 10.0f};
    glm::vec3 dir{-0.25f, -0.25f, -1.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};

    glm::mat4 getView() {
        dir = glm::normalize(dir);
        return glm::lookAt(pos, pos + dir, up);
    }
} Camera;

