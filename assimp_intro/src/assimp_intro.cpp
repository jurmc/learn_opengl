#include "main.hpp"
#include "assimp_intro.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>

Loader::Loader(const std::string &filename) :
    mFilename(std::string(filename)),
    mImporter() {
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

