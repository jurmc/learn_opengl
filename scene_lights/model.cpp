#include "model.hpp"
#include "material.hpp"

#include "glad/glad.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <print>

Model::Model(const char *fileName) :
    meshes(),
    materials(),
    meshInstances()
{
    Assimp::Importer importer;
    auto scene = importer.ReadFile(
            fileName,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    std::println("--materials");
    for (uint32_t i = 0; i < scene->mNumMaterials; ++i) {
        aiMaterial *m = scene->mMaterials[i];
        std::println("mat: {}", i);
        std::println("numProp: {}", m->mNumProperties); 
        aiColor4D diffuse(0.0f, 0.0f, 0.0f, 1.0f);
        if (AI_SUCCESS != m->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse)) {
            std::println("cannto obtain diffuse color");
        }

        Material material{
            glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a),
        };
        materials.push_back(material);
    }
    std::println("---------");

    for (uint32_t i = 0; i < scene->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[i];

        std::println("mesh: {}", mesh->mName.C_Str());
        std::println("mat idx: {}", mesh->mMaterialIndex);

        std::string meshName(mesh->mName.C_Str());
        std::vector<float> vertices;
        for (uint32_t j = 0; j < mesh->mNumVertices; ++j) {
            aiVector3D v = mesh->mVertices[j];
            vertices.push_back(v.x);
            vertices.push_back(v.y);
            vertices.push_back(v.z);
        }
        std::vector<uint32_t> indices;
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace f = mesh->mFaces[j];
            assert(3 == f.mNumIndices);
            indices.push_back(f.mIndices[0]);
            indices.push_back(f.mIndices[1]);
            indices.push_back(f.mIndices[2]);
        }

        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);

        Mesh newMesh{
            mesh->mName.C_Str(),
            std::move(vertices),
            std::move(indices),
            mesh->mMaterialIndex, 
            VAO,
        };

        meshes.push_back(std::move(newMesh));
    }

    aiMatrix4x4 identity;
    traverseScene(scene->mRootNode, identity);
}

void Model::traverseScene(const aiNode *node, aiMatrix4x4 parentTransform) {
    std::string name = node->mName.C_Str();

    aiMatrix4x4 transform = node->mTransformation;

    aiMatrix4x4 accTransform = parentTransform;
    for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
        uint32_t meshIdx = node->mMeshes[i];
        accTransform = parentTransform * transform;
        MeshInstance meshInstance{
            meshIdx,
            glm::transpose(glm::make_mat4(&accTransform.a1)),
        };
        meshInstances[name] = meshInstance;
    }

    for (uint32_t i = 0; i < node->mNumChildren; ++i) {
        traverseScene(node->mChildren[i], accTransform);
    }
}

