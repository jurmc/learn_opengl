#include "mesh.hpp"

#include "glad/glad.h"

#include <vector>
#include <glm/glm.hpp>

Mesh::Mesh(std::tuple<Vertices, Indices> &tuple, unsigned int GPUTextureId) : mGPUTextureId(GPUTextureId) {
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

    // irst 3 floats are 3D coords, then next 2 floats are UV coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

    mVaosAndIndicesNums.push_back(std::tuple<unsigned int, size_t>(VAO, indicesNum));
}

void Mesh::Draw(const Shader &shader) {
    shader.use();
    shader.setInt("ourTexture", 0); // TODO: this might be a call in constructor, it not need to be repeated upon Draw() calls
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mGPUTextureId);

    // TODO: is this loop really needed? mesh is just one I think...
    for (auto& [vao, num] : mVaosAndIndicesNums) {
        static std::vector<glm::vec4> colors {
            glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                glm::vec4(0.1f, 0.32f, 0.26f, 1.0f),
                glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
        };

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, num, GL_UNSIGNED_INT, 0);
    }
}

