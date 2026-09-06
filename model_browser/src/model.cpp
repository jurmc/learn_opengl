#include "main.hpp"
#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>
#include <cassert>
#include <utility>
#include <tuple>
#include <set>

Model::Model(const std::string &filename) :
    mMeshes(),
    mFilename(std::string(filename))
    {

    Assimp::Importer importer;
    mScene = importer.ReadFile(
            mFilename,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    if (nullptr == mScene) { // TODO: wider check, see Joey The Vries
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

                    assert(m->mNumUVComponents[0] > 0);

                    for (auto i = 0u; i < m->mNumVertices; ++i) {
                        vertices.push_back(m->mVertices[i].x);
                        vertices.push_back(m->mVertices[i].y);
                        vertices.push_back(m->mVertices[i].z);

                        vertices.push_back(m->mTextureCoords[0][i].x);
                        vertices.push_back(m->mTextureCoords[0][i].y);
                    }

                    assert(m->HasFaces());

                    for (auto i = 0u; i < m->mNumFaces; ++i) {
                        auto face = m->mFaces[i];
                        assert(3 == face.mNumIndices);

                        indices.push_back(face.mIndices[0]);
                        indices.push_back(face.mIndices[1]);
                        indices.push_back(face.mIndices[2]);
                    }

                    std::println("Num vertices: {}", m->mNumVertices);
                    std::println("Vec size: {}", vertices.size());

                    auto newMesh = std::tuple<Vertices, Indices>(vertices, indices);
                    mMeshes.push_back(Mesh(newMesh));
                }
            }
        }
    }
}

void Model::Draw(const Shader &shader) {
    for (auto& m: mMeshes) {
        m.Draw(shader);
    }
}
