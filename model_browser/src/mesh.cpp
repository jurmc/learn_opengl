#include "mesh.hpp"

#include "glad/glad.h"

#include <vector>
#include <glm/glm.hpp>

Mesh::Mesh(std::tuple<Vertices, Indices> &tuple) {
    auto [vertices, indices] = tuple;
    auto verticesNum = vertices.size();
    auto verticesSize = sizeof(float) * verticesNum;

    auto indicesNum = indices.size();
    auto indicesSize = sizeof(unsigned int) * indicesNum;

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

    mVaosAndIndicesNums.push_back(std::tuple<unsigned int, size_t>(VAO, indicesNum));
}

void Mesh::Draw(const Shader &shader) {
    shader.use();
    unsigned int colorId = 1;

    for (auto& [vao, num] : mVaosAndIndicesNums) {
        static std::vector<glm::vec4> colors {
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                glm::vec4(0.1f, 0.32f, 0.26f, 1.0f),
                glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
        };

        shader.setVec4("color", colors[colorId]);
        ++colorId;
        if (colorId >= colors.size()) {
            colorId = 0;
        }

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_INT, 0);
    }
}

