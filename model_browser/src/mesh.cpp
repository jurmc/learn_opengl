#include "mesh.hpp"

#include "glad/glad.h"

#include <glm/glm.hpp>

Mesh::Mesh(Vertices vertices, Indices indices, unsigned int GPUTextureId) : mGPUTextureId(GPUTextureId) {
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

    // first 3 floats are 3D coords, then next 2 floats are UV coords
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // TODO: next, we gonna add normals

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_STATIC_DRAW);

    mVao = VAO;
    mIdxCnt = indicesNum;
}

void Mesh::Draw(const Shader &shader) {
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mGPUTextureId);
    glBindVertexArray(mVao);
    glDrawElements(GL_TRIANGLES, mIdxCnt, GL_UNSIGNED_INT, 0);
}

