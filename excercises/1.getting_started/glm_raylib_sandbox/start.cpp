#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

#include<iostream>

int main(void) {
    glm::vec3 v(1.0f, 2.0f, 3.0f);

    std::cout << "vec is: " << v.x << " " << v.y << " " << v.z << " " << std::endl;
    float f = 5.0f;
    auto r = v / f;
    std::cout << "result is: " << r.x << " " << r.y << " " << r.z << std::endl;

    glm::vec3 nv = -v;
    std::cout << "nv is: " << nv.x << " " << nv.y << " " << nv.z << std::endl;

    glm::vec3 nv2 = (-1.0f) * v;
    std::cout << "nv2 is: " << nv2.x << " " << nv2.y << " " << nv2.z << std::endl;

    std::cout << "-------------------" << std::endl;
    glm::vec3 v1(1.0f, 2.0f, 3.0f);
    glm::vec3 v2(4.0f, 5.0f, 6.0f);
    glm::vec3 v3 = v1 + v2;
    std::cout << "v3 is: " << v3.x << " " << v3.y << " " << v3.z << std::endl;

    std::cout << "-------------------" << std::endl;
    glm::vec2 vv(4.0f, 2.0f);
    std::cout << "length: " << glm::length(vv) << std::endl;
    auto vv_norm = glm::normalize(vv);
    std::cout << "vv_norm is: " << vv_norm.x << " " << vv_norm.y << std::endl;
    std::cout << "length vv_norm: " << glm::length(vv_norm) << std::endl;

    return 0;
}
