#include "main.hpp"
#include "assimp_intro.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>

std::vector<float> LoadModel() { // Temporary
    std::vector<float> v{
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
    };

    return v;
}

std::vector<float> LoadModel2() { // Temporary
    std::print("Hello Assimp\n");
    std::vector<float> vertices;

    Assimp::Importer importer;

    auto scene = importer.ReadFile(
            "../kenney_car-kit/Models/GLB format/cone.glb",
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    if (nullptr == scene) {
        std::printf("Error while importing file\n"); // TODO: printf into stderr
        // TODO: exit error here

        return vertices;
    }

    if (scene->mNumMeshes > 0) {
        auto m = scene->mMeshes[0];

        vertices.reserve(m->mNumVertices * 3);
        for (auto i = 0u; i < m->mNumVertices; i = i+3) {
            vertices.push_back(m->mVertices[i].x);
            vertices.push_back(m->mVertices[i].y);
            vertices.push_back(m->mVertices[i].z);
        }
    }

    return vertices;
}

Loader::Loader(const std::string &filename) {
    mFilename = std::string(filename);

    Assimp::Importer importer;
    auto scene = importer.ReadFile(
            mFilename,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    if (nullptr == scene) {
        std::printf("Error while importing file\n"); // TODO: printf into stderr
        // TODO: exit error here
    }

    if (scene->mNumMeshes > 0) {
        auto m = scene->mMeshes[0];

        mVertices.reserve(m->mNumVertices * 3);
        for (auto i = 0u; i < m->mNumVertices; i = i+3) {
            mVertices.push_back(m->mVertices[i].x);
            mVertices.push_back(m->mVertices[i].y);
            mVertices.push_back(m->mVertices[i].z);
        }
    }
}

int main_assimp([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    Loader l("../kenney_car-kit/Models/GLB format/cone.glb");
    auto v = l.getVertices();

    for (size_t i = 0; i < v.size(); i += 3) {
        std::print("v: {},{},{}\n", v[i], v[i+1], v[i+2]);
    }

    return 0;
}


