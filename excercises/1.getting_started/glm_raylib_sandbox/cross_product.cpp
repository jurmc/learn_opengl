#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

#include <raymath.h>

#include <iostream>

int main(void) {
    std::cout << "Cross product" << std::endl;

    std::cout << "-- GLM" << std::endl;
    glm::vec3 v1(1.0f, 0.0f, 0.0f);
    glm::vec3 v2(0.0f, 1.0f, 0.0f);

    glm::vec3 v3 = glm::cross(v1, v2);
    std::cout << "v3: " << v3.x << ", " << v3.y << ", " << v3.z << std::endl;

    std::cout << "-- Raymath" << std::endl;
    Vector3 rv1 = {1.0f, 0.0f, 0.0f};
    Vector3 rv2 = {0.0f, 1.0f, 0.0f};

    Vector3 rv3 = Vector3CrossProduct(rv1, rv2);
    std::cout << "rv3: " << rv3.x << ", " << rv3.y << ", " << rv3.z << std::endl;

    return 0;
}
