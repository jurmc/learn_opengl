#include "camera.hpp"
#include "shader.hpp"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <print>
#include <string>
#include <vector>
#include <cassert>

void dumpAiMatrix(const aiMatrix4x4 &m) {
    std::println("{}, {}, {}, {}", m.a1, m.a2, m.a3, m.a4);
    std::println("{}, {}, {}, {}", m.b1, m.b2, m.b3, m.b4);
    std::println("{}, {}, {}, {}", m.c1, m.c2, m.c3, m.c4);
    std::println("{}, {}, {}, {}", m.d1, m.d2, m.d3, m.d4);
}

void traverse(const aiNode *node, std::string prefix) {
    std::string name = node->mName.C_Str();
    if (name.starts_with("ROOT") || name.starts_with("Plane")) {
        std::println("nodeName: {}", name);
        aiMatrix4x4 transform = node->mTransformation;
        dumpAiMatrix(transform);
        std::println();
        for (int i = 0; i < node->mNumChildren; ++i) {
            traverse(node->mChildren[i], prefix + " ");
        }
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
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

    std::println("num meshes: {}", scene->mNumMeshes);
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[i];
        std::string name(mesh->mName.C_Str());
        if (name.starts_with("Plane")) {
            std::println(" name: {}", name);
            for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
                aiVector3D v = mesh->mVertices[j];
                planeVertices.push_back(v.y);
                planeVertices.push_back(v.z);
                planeVertices.push_back(v.x);
                std::println("  v: {},{},{}", v.x, v.y, v.z);
            }

            for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
                aiFace f = mesh->mFaces[j];
                assert(3 == f.mNumIndices);
                planeIndices.push_back(f.mIndices[0]);
                planeIndices.push_back(f.mIndices[1]);
                planeIndices.push_back(f.mIndices[2]);
                std::println(" i: {},{},{}", f.mIndices[0], f.mIndices[1], f.mIndices[2]);
            }
        }
    }

    std::println("----------------------");
    std::println("traversing nodes");
    traverse(scene->mRootNode, "");


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

    glfwSetKeyCallback(window, key_callback);

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * planeVertices.size(), planeVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * planeIndices.size(), planeIndices.data(), GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    Shader shader("default.vs", "default.fs");

    Camera camera;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.setMat4("model", glm::mat4(1.0f));
        shader.setMat4("view", camera.getView());
        shader.setMat4("perspective", glm::perspective( glm::radians(45.0f), (float)w/h, 0.1f, 100.0f));

        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, planeIndices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
