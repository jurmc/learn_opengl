#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

#include <raymath.h>

#include <iostream>

int main(void) {
    std::cout << "Dot product" << std::endl;

    std::cout << "-- GLM" << std::endl;
    glm::vec2 v1(0.6f, -0.8f);
    glm::vec2 v2(0.0f, 1.0f);

    float c = glm::dot(v1, v2);
    float a = glm::degrees(acos(c));
    std::cout << "c: " << c << std::endl;
    std::cout << "a: " << a << std::endl;

    std::cout << "-- Raymath" << std::endl;
    Vector2 rv1 = {0.6f, -0.8f};
    Vector2 rv2 = {0.0f, 1.0f};

    float rc = Vector2DotProduct(rv1, rv2);
    float ra = RAD2DEG * (acos(c));
    std::cout << "rc: " << rc << std::endl;
    std::cout << "ra: " << ra << std::endl;

    return 0;
}
