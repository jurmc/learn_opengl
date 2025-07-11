#include<glm/mat2x2.hpp>
#include<glm/mat3x3.hpp>
#include<glm/matrix.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/string_cast.hpp>

#include<raymath.h>

#include<iostream>

int main(void) {
    std::cout << "Matrix operations" << std::endl;

    std::cout << "Glm" << std::endl;
    glm::mat2x2 m1(1.0f, 3.0f, 2.0f, 4.0f);
    glm::mat2x2 m2(5.0f, 7.0f, 6.0f, 8.0f);
    glm::mat2x2 r1 = m1 + m2;
    std::cout << "r1:" << glm::to_string(r1) << std::endl;

    glm::mat2x2 m3(4.0f, 1.0f, 2.0f, 6.0f);
    glm::mat2x2 m4(2.0f, 0.0f, 4.0f, 1.0f);
    glm::mat2x2 r2 = m3 - m4;
    std::cout << "r2:" << glm::to_string(r2) << std::endl;

    glm::mat3x3 m5 = {4, 0, 0,
                      2, 8, 1,
                      0, 1, 0};
    glm::mat3x3 m6 = {4, 2, 9,
                      2, 0, 4,
                      1, 4, 2};
    auto r3 = m5 * m6;
    std::cout << "r3:" << glm::to_string(r3) << std::endl;


    return 0;
}
