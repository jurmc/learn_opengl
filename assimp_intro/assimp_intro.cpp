#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>

int main(int argc, char **argv) {
    std::print("Hello Assimp\n");

    Assimp::Importer importer;

    auto scene = importer.ReadFile(
            "../kenney_car-kit/Models/GLB format/cone.glb",
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    if (nullptr == scene) {
        std::print("Error while importing file\n");
        return false;
    }

    std::print("mNumMeshes: {}\n", scene->mNumMeshes);

    if (scene->mNumMeshes > 0) {
        auto m = scene->mMeshes[0];

        std::print("HasBones: {}\n", m->HasBones());
        std::print("HasFaces: {}\n", m->HasFaces());
        std::print("HasNormals: {}\n", m->HasNormals());
        std::print("HasPositions: {}\n", m->HasPositions());

        std::print("mNumFaces: {}\n", m->mNumFaces);
        std::print("mNumVertices: {}\n", m->mNumVertices);
    }


    return 0;
}

