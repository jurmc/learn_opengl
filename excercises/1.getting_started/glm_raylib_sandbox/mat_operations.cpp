#include<glm/mat2x2.hpp>
#include<glm/mat3x3.hpp>
#include<glm/mat4x4.hpp>
#include<glm/matrix.hpp>
#include<glm/ext/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/string_cast.hpp>

#include<raymath.h>

#include<iostream>

void dump_raymath_matrix(Matrix m) {
    std::cout << m.m0 << " " << m.m1 << " " << m.m2 << " " << m.m3 << std::endl;
    std::cout << m.m4 << " " << m.m5 << " " << m.m6 << " " << m.m7 << std::endl;
    std::cout << m.m8 << " " << m.m9 << " " << m.m10 << " " << m.m11 << std::endl;
    std::cout << m.m12 << " " << m.m13 << " " << m.m14 << " " << m.m15 << std::endl;
}

int main(void) {
    std::cout << "-- Matrix operations" << std::endl;

    std::cout << "-- Glm" << std::endl;
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

    glm::mat4 iden4 = glm::mat4(1);
    glm::vec4 v4(1.0f, 2.0f, 3.0f, 4.0f);
    glm::vec4 result = iden4 * v4;
    std::cout << "Glm identity matrix: " << glm::to_string(iden4) << std::endl;
    std::cout << "Result: " << glm::to_string(result) << std::endl;

    glm::mat4 scale = iden4;
    scale[0][0] = 0.5f; scale[1][1] = 2.0f; scale[2][2] = 1.0f;
    glm::vec4 vec4scale(3, 2, 0, 1);
    glm::vec4 scaled = scale * vec4scale;

    std::cout << "Scaled vec: "<< glm::to_string(scaled) << std::endl;

    glm::vec4 vec_to_trans(1.0f, 2.0f, 3.0f, 1.0f);
    glm::vec3 trans_vector(1, 2, 3);
    glm::mat4 trans_matrix = glm::translate(iden4, trans_vector);
    std::cout << "Trans matrix: "<< glm::to_string(trans_matrix) << std::endl;
    glm::vec4 translated_v4 = trans_matrix * vec_to_trans;
    std::cout << "Trans vec: "<< glm::to_string(translated_v4) << std::endl;

    std::cout << "-- Raymath" << std::endl;
    Matrix m = MatrixIdentity();
    dump_raymath_matrix(m);

    return 0;
}
