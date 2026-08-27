#include "main.hpp"
#include "loader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>
#include <cassert>

Loader::Loader(const std::string &filename) :
    mFilename(std::string(filename)),
    mImporter(),
    mVertices(),
    mIndices(),
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
            mVertices.insert(mVertices.begin(), arrVertices, arrVertices + std::size(arrVertices));

            unsigned int arrIndices[] = {
                0, 1, 2,
                0, 3, 4,
                0, 5, 6,
                0, 7, 8,
            };
            mIndices.insert(mIndices.begin(), arrIndices, arrIndices + std::size(arrIndices));

            mMeshes.push_back(std::tuple<Vertices, Indices>(mVertices, mIndices));

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
        if (   mScene->mRootNode
            && mScene->HasMeshes()) {
            if (mScene->mRootNode->mNumMeshes > 0) {
                auto meshIdx = mScene->mRootNode->mMeshes[0];
                auto m = mScene->mMeshes[meshIdx];

                for (auto i = 0u; i < m->mNumVertices; ++i) {
                    mVertices.push_back(m->mVertices[i].x);
                    mVertices.push_back(m->mVertices[i].y);
                    mVertices.push_back(m->mVertices[i].z);
                }

                assert(m->HasFaces());

                for (auto i = 0u; i < m->mNumFaces; ++i) {
                    auto face = m->mFaces[i];
                    assert(3 == face.mNumIndices);

                    mIndices.push_back(face.mIndices[0]);
                    mIndices.push_back(face.mIndices[1]);
                    mIndices.push_back(face.mIndices[2]);
                }
            }
        }
    }

}

