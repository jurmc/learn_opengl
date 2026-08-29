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
                    mMeshes.push_back(std::tuple<Vertices, Indices>(vertices, indices));
                }
            }
        }
    }

}

