#include "model.hpp"
#include "material.hpp"

#include "glad/glad.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <print>
#include <stb/stb_image.h>

Mesh createUntexturedMesh(const char* meshName,
        std::vector<VertexUntextured>& vertices,
        std::vector<unsigned int>& indices,
        unsigned int matIdx) {

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexUntextured), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUntextured), (void*)offsetof(VertexUntextured, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexUntextured), (void*)offsetof(VertexUntextured, normal));
    glEnableVertexAttribArray(1);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);

    Mesh m{
        meshName,
        indices.size(),
        matIdx, 
        false,
        VAO,
    };

    return m;
}

Mesh createTexturedMesh(const char* meshName,
        std::vector<VertexTextured>& vertices,
        std::vector<unsigned int>& indices,
        unsigned int matIdx) {

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexTextured), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (void*)offsetof(VertexTextured, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (void*)offsetof(VertexTextured, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexTextured), (void*)offsetof(VertexTextured, texCoords));
    glEnableVertexAttribArray(2);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);

    Mesh m{
        meshName,
        indices.size(),
        matIdx, 
        true,
        VAO,
    };

    return m;
}

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

    // load material, TODO: maybe this can be extracted?

    std::println("--materials");
    for (uint32_t i = 0; i < scene->mNumMaterials; ++i) {
        aiMaterial *m = scene->mMaterials[i];
        std::println("mat: {}", i);
        std::println("numProp: {}", m->mNumProperties); 

        // Textrue (if exist) has precedence
        if (m->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
            aiString texturePath;
            if (aiReturn_FAILURE == m->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath)) {
                std::println(stderr, "Cannot get texture path");
                std::exit(1);
            }
            const aiTexture* embeddedTexture = scene->GetEmbeddedTexture(texturePath.C_Str());
            if (embeddedTexture) {
                std::println("this is embedded texture");

                int w, h, n;
                //unsigned char *texData = stbi_load_from_memory(
                //        reinterpret_cast<const stbi_uc*>(embeddedTexture->pcData),
                //        embeddedTexture->mWidth,
                //        &w, &h, &n, 3);
                unsigned char *texData = stbi_load("checkered.png", &w, &h, &n, 3);
                if (!texData) {
                    std::println("sth wrong with stbi_load");
                }

                /////
                unsigned int textureId;
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                if (texData) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
                    glGenerateMipmap(GL_TEXTURE_2D);
                } else {
                    std::println(stderr, "Cannot load image");
                }
                stbi_image_free(texData);

                Material material{
                    MaterialType::Texture,
                        glm::vec4(0.1f, 0.1f, 0.1f, 0.1f),
                        textureId,
                };
                std::println("tex id: {}", material.textureId);
                materials.push_back(material);
            }
            /////
        } else {
            aiColor4D diffuse(0.0f, 0.0f, 0.0f, 1.0f);
            if (AI_SUCCESS != m->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse)) {
                std::println("can't obtain diffuse color");
            }
            Material material{
                MaterialType::Color,
                glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a),
                0,
            };
            materials.push_back(material);
        }
    }

    for (uint32_t i = 0; i < scene->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[i];

        if (MaterialType::Texture == materials[mesh->mMaterialIndex].type) {

            std::vector<VertexTextured> vertices;
            for (uint32_t j = 0; j < mesh->mNumVertices; ++j) {
                aiVector3D v = mesh->mVertices[j];
                aiVector3D n = mesh->mNormals[j];
                aiVector3D uv = mesh->mTextureCoords[0][j];
                vertices.push_back(VertexTextured{
                        glm::vec3(v.x, v.y, v.z),
                        glm::vec3(n.x, n.y, n.z),
                        glm::vec2(uv.x, uv.y),
                        });
            }
            std::vector<uint32_t> indices;
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
                aiFace f = mesh->mFaces[j];
                assert(3 == f.mNumIndices);
                indices.push_back(f.mIndices[0]);
                indices.push_back(f.mIndices[1]);
                indices.push_back(f.mIndices[2]);

            }

            Mesh m = createTexturedMesh(mesh->mName.C_Str(),
                    vertices, indices,
                    mesh->mMaterialIndex);
            meshes.push_back(std::move(m));
        } else {
            std::vector<VertexUntextured> vertices;
            for (uint32_t j = 0; j < mesh->mNumVertices; ++j) {
                aiVector3D v = mesh->mVertices[j];
                aiVector3D n = mesh->mNormals[j];
                vertices.push_back(VertexUntextured{
                        glm::vec3(v.x, v.y, v.z),
                        glm::vec3(n.x, n.y, n.z),
                        });
            }
            std::vector<uint32_t> indices;
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
                aiFace f = mesh->mFaces[j];
                assert(3 == f.mNumIndices);
                indices.push_back(f.mIndices[0]);
                indices.push_back(f.mIndices[1]);
                indices.push_back(f.mIndices[2]);

            }

            Mesh m = createUntexturedMesh(mesh->mName.C_Str(),
                    vertices, indices,
                    mesh->mMaterialIndex);
            meshes.push_back(std::move(m));
        }
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

