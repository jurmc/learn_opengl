#include "main.hpp"
#include "loader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>

Loader::Loader(const std::string &filename) :
    mFilename(std::string(filename)),
    mImporter(),
    mVertices()
    {
        if ("test" == filename) {
            mScene = new aiScene();

            float arr[] = {
                //0.2f, 0.2f, 0.2f,   
                //-0.2f, -0.2f, -0.2f,   

                0.1f, 0.1f, 0.0f,
                0.7f, 0.1f, 0.0f,
                0.7f, 0.7f, 0.0f,

                0.1f, -0.1f, 0.0f,
                0.7f, -0.1f, 0.0f,
                0.7f, -0.7f, 0.0f,

                -0.1f, 0.1f, 0.0f,
                -0.7f, 0.1f, 0.0f,
                -0.7f, 0.7f, 0.0f,

                -0.1f, -0.1f, 0.0f,
                -0.7f, -0.1f, 0.0f,
                -0.7f, -0.7f, 0.0f,
            };
            mVertices.insert(mVertices.begin(), arr, arr + std::size(arr));

            for (auto &i : mVertices) {
                std::println("i: {}", i);
            }

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
        for (size_t i = 0; i < mScene->mNumMeshes; ++i) {
            auto m = mScene->mMeshes[i];

            mVertices.reserve(m->mNumVertices * 3);
            for (auto j = 0u; j < m->mNumVertices; j = j+3) {
                mVertices.push_back(m->mVertices[j].x);
                mVertices.push_back(m->mVertices[j].y);
                mVertices.push_back(m->mVertices[j].z);
            }
        }
    }
}

