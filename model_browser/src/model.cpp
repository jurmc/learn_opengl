#include "main.hpp"
#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <print>
#include <vector>
#include <cassert>
#include <utility>
#include <tuple>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

Model::Model(const std::string &filename) :
    mMeshes(),
    mFilename(std::string(filename)),
    mImporter()
    {

    mScene = mImporter.ReadFile(
            mFilename,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    if (nullptr == mScene) { // TODO: wider check, see Joey The Vries
        std::print(stderr, "Error while importing file\n");
        // TODO: exit error here
    }

    for (size_t i = 0; i < mScene->mNumMaterials; ++i) {
        auto material = mScene->mMaterials[i];
        auto texCnt = material->GetTextureCount(aiTextureType_DIFFUSE);
        if (texCnt > 0) {
            aiString filePath;
            material->GetTexture(aiTextureType_DIFFUSE, 0, &filePath);
            std::string fullFilePath = std::string(fs::path(fs::path(mFilename).parent_path())) + "/" + filePath.C_Str();
            Texture texture(fullFilePath.c_str());
            mTextures.insert({i, texture});
        }
    }

    if (mScene->mNumMeshes > 0) {
        if (   mScene && mScene->HasMeshes()) {
            if (mScene->mNumMeshes > 0) {
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

                    auto mesh = std::tuple<Vertices, Indices>(vertices, indices);
                    unsigned int GPUTextureId = mTextures.at(m->mMaterialIndex).getGPUId();
                    mMeshes.push_back(Mesh(mesh, GPUTextureId));
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
