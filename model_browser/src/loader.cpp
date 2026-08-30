#include "main.hpp"
#include "loader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>
#include <cassert>
#include <utility>

Loader::Loader(const std::string &filename) :
    mVaosAndIndicesNums(),
    mFilename(std::string(filename)),
    mImporter(),
    mMeshes()
    {
        if ("test" == filename) {
            mScene = new aiScene();

            float arrVertices[] = {
                0.0f, 0.0f, 0.0f,

                0.7f, 0.1f, 0.0f,
                0.7f, 0.7f, 0.0f,

                0.7f, -0.1f, 0.0f,
                0.7f, -0.7f, 0.0f,

                -0.7f, 0.1f, 0.0f,
                -0.7f, 0.7f, 0.0f,

                -0.7f, -0.1f, 0.0f,
                -0.7f, -0.7f, 0.0f,
            };

            Vertices vertices;
            Indices indices;

            vertices.insert(vertices.begin(), arrVertices, arrVertices + std::size(arrVertices));

            unsigned int arrIndices[] = {
                0, 1, 2,
                0, 3, 4,
                0, 5, 6,
                0, 7, 8,
            };
            indices.insert(indices.begin(), arrIndices, arrIndices + std::size(arrIndices));

            mMeshes.push_back(std::tuple<Vertices, Indices>(vertices, indices));

            Vertices secondMesh{};
            for (size_t i = 0; i < indices.size(); i += 3) {
                secondMesh.push_back(indices[i]);
                secondMesh.push_back(indices[i+1]);
                secondMesh.push_back(indices[i+2]-0.5);
            }

            mMeshes.push_back(std::tuple<Vertices, Indices>(secondMesh, indices));

            return;
    }

    mScene = mImporter.ReadFile(
            mFilename,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    if (nullptr == mScene) {
        std::print(stderr, "Error while importing file\n");
        // TODO: exit error here
    }

    if (mScene->mNumMeshes > 0) {
        if (   mScene && mScene->HasMeshes()) {
            if (mScene->mNumMeshes > 0) {
                std::println("mNumMeshes: {}", mScene->mNumMeshes);
                for (size_t i = 0; i < mScene->mNumMeshes; ++i) {
                    auto m = mScene->mMeshes[i];

                    Vertices vertices;
                    Indices indices;

                    for (auto i = 0u; i < m->mNumVertices; ++i) {
                        vertices.push_back(m->mVertices[i].x);
                        vertices.push_back(m->mVertices[i].y);
                        vertices.push_back(m->mVertices[i].z);
                    }

                    assert(m->HasFaces());

                    for (auto i = 0u; i < m->mNumFaces; ++i) {
                        auto face = m->mFaces[i];
                        assert(3 == face.mNumIndices);

                        indices.push_back(face.mIndices[0]);
                        indices.push_back(face.mIndices[1]);
                        indices.push_back(face.mIndices[2]);
                    }

                    std::println("loaded: ver num {}, ind num {}", vertices.size(), indices.size());
                    auto newMesh = std::tuple<Vertices, Indices>(vertices, indices);
                    ProsessMesh(newMesh);
                    mMeshes.push_back(newMesh);
                }
            }
        }
    }

}

void Loader::ProsessMesh(std::tuple<Vertices, Indices> &tuple) {
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

void Loader::Draw(const Shader &shader) {
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
