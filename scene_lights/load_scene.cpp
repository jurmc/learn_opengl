#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "config.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"

#include <glm/ext.hpp>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <print>
#include <vector>
#include <cassert>
#include <cstdint>
#include <utility>

void key_callback(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
    SceneConfig config {
        .lightSource = {
            .color = glm::vec4(1.0f)
        },
    }; // Maybe we need construcor?

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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    std::println("version: {}", version);

    Shader shaderDiffuseColor("shaders/default.vs", "shaders/diffuseColor.fs");
    Shader shaderTexture("shaders/default.vs", "shaders/texture.fs");
    Shader shaderLightSource("shaders/lightSource.vs", "shaders/lightSource.fs");
    Model model("scene.glb", config);
    if (false == config.lightSource.initialized) {
        std::println(stderr, "light source mesh not found");
        std::exit(1);
    }

    Camera camera;
    float a = 0.0f;
    float r = 8.0f;

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Light scene for Learn OpenGL");
        auto lsCol = &config.lightSource.color;
        float color[3] = {lsCol->x, lsCol->y, lsCol->z};
        if (ImGui::ColorEdit3("Light color", (float*)&color)) {
            lsCol->x = color[0];
            lsCol->y = color[1];
            lsCol->z = color[2];
        }
        auto lsPos = &config.lightSource.position;
        float pos[3]{lsPos->x, lsPos->y, lsPos->z};
        if (ImGui::InputFloat3("Camera pos", pos)) {
            lsPos->x = pos[0];
            lsPos->y = pos[1];
            lsPos->z = pos[2];
            glm::mat4 lightModel = glm::mat4(1.0f); // TODO: duplicated code
            lightModel = glm::translate(lightModel, config.lightSource.position);
            auto SCALE = 0.25f;
            lightModel = glm::scale(lightModel, glm::vec3(SCALE));
            config.lightSource.transform = lightModel;
        }
        ImGui::End();

        a = 0.5f * glfwGetTime();
        camera.pos.x = r * glm::cos(a);
        camera.pos.z = r * glm::sin(a);
        camera.dir.x = -camera.pos.x;
        camera.dir.z = -camera.pos.z;

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderTexture.use();
        shaderTexture.setMat4("view", camera.getView());
        shaderTexture.setMat4("perspective", glm::perspective( glm::radians(45.0f), (float)w/h, 0.1f, 100.0f));
        shaderDiffuseColor.use();
        shaderDiffuseColor.setMat4("view", camera.getView());
        shaderDiffuseColor.setMat4("perspective", glm::perspective( glm::radians(45.0f), (float)w/h, 0.1f, 100.0f));
        shaderLightSource.use();
        shaderLightSource.setMat4("view", camera.getView());
        shaderLightSource.setMat4("perspective", glm::perspective( glm::radians(45.0f), (float)w/h, 0.1f, 100.0f));

        // Scene objects
        for (auto &[name, meshInstance]: model.meshInstances) {
            uint32_t meshIdx = meshInstance.idx;
            const Mesh &mesh = model.meshes[meshIdx];
            const Material &material = model.materials[mesh.materialIdx];
            if (material.type == MaterialType::Texture) {
                shaderTexture.use();
                shaderTexture.setFloat("ambientColComponent", 0.2f);
                shaderTexture.setMat4("model", meshInstance.transform);
                shaderTexture.setFloat("diffuseColComponent", 0.8f);
                shaderTexture.setVec4("lightSourceColor", config.lightSource.color);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, material.textureId);
                shaderTexture.setInt("textureId", 0);
            } else {
                shaderDiffuseColor.use();
                shaderDiffuseColor.setFloat("ambientColComponent", 0.2f);
                shaderDiffuseColor.setVec4("ambientCol", material.diffuse);
                shaderDiffuseColor.setMat4("model", meshInstance.transform);
                shaderDiffuseColor.setFloat("diffuseColComponent", 0.8f);
                shaderDiffuseColor.setVec4("diffuseCol", material.diffuse);
                shaderDiffuseColor.setVec4("lightSourceColor", config.lightSource.color);
            }

            glBindVertexArray(mesh.vao);
            glDrawElements(GL_TRIANGLES, mesh.indexCnt, GL_UNSIGNED_INT, 0);
        }

        // Light source
        shaderLightSource.use();
        shaderLightSource.setMat4("model", config.lightSource.transform);
        glBindVertexArray(config.lightSource.vao);
        glDrawElements(GL_TRIANGLES, config.lightSource.indexCnt, GL_UNSIGNED_INT, 0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}
