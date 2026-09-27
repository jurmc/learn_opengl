#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"

#include "glad/glad.h"

#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <string>
#include <vector>
#include <cassert>
#include <cstdint>
#include <utility>

void dumpAiMatrix(const aiMatrix4x4 &m) {
    std::println("{}, {}, {}, {}", m.a1, m.a2, m.a3, m.a4);
    std::println("{}, {}, {}, {}", m.b1, m.b2, m.b3, m.b4);
    std::println("{}, {}, {}, {}", m.c1, m.c2, m.c3, m.c4);
    std::println("{}, {}, {}, {}", m.d1, m.d2, m.d3, m.d4);
}

void traverse_scene(const aiNode *node, Model &model, aiMatrix4x4 parentTransform) {
    std::string name = node->mName.C_Str();

    std::println("nodeName: {}", name);
    aiMatrix4x4 transform = node->mTransformation;

    aiMatrix4x4 accTransform = parentTransform;
    for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
        uint32_t meshIdx = node->mMeshes[i];
        accTransform = parentTransform * transform;
        MeshInstance meshInstance{
            meshIdx,
            //glmParentTransform * glmNodeTransform,
            glm::transpose(glm::make_mat4(&accTransform.a1)),
        };
        model.meshInstances[name] = meshInstance;
    }

    dumpAiMatrix(transform);
    std::println();
    for (uint32_t i = 0; i < node->mNumChildren; ++i) {
        traverse_scene(node->mChildren[i], model, accTransform);
    }
}

void key_callback(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
    Assimp::Importer importer;
    auto scene = importer.ReadFile(
            "scene.glb",
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

    std::vector<float> planeVertices{};
    std::vector<unsigned int> planeIndices{};

    // Window
    int w = 800;
    int h = 600;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(w, h, "Scene for lighting", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::println("version: {}", version);

    glfwSetKeyCallback(window, key_callback);
    Shader shader("default.vs", "default.fs");

    Model model;
    std::println("num meshes: {}", scene->mNumMeshes);
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[i];

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
                VAO,
        };

        model.meshes.push_back(std::move(newMesh));
    }

    std::println("traversing nodes");
    aiMatrix4x4 identity;
    traverse_scene(scene->mRootNode, model, identity);

    Camera camera;
    float a = 0.0f;
    float r = 8.0f;


    while (!glfwWindowShouldClose(window)) {

        a = 0.5f * glfwGetTime();
        camera.pos.x = r * glm::cos(a);
        camera.pos.z = r * glm::sin(a);
        camera.dir.x = -camera.pos.x;
        camera.dir.z = -camera.pos.z;

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setMat4("view", camera.getView());
        shader.setMat4("perspective", glm::perspective( glm::radians(45.0f), (float)w/h, 0.1f, 100.0f));

        shader.use();
        for (auto &[name, meshInstance]: model.meshInstances) {
            uint32_t meshIdx = meshInstance.idx;
            shader.setMat4("model", meshInstance.transform);
            glBindVertexArray(model.meshes[meshIdx].vao);
            glDrawElements(GL_TRIANGLES, model.meshes[meshIdx].indices.size(), GL_UNSIGNED_INT, 0);
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
