#include "camera.hpp"
#include "shader.hpp"
#include "model.hpp"
#include "config.hpp"
#include "gui.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLFW/glfw3.h>

#include <print>
#include <cassert>
#include <cstdint>
#include <utility>
#include <cmath>

const double PI = glm::pi<double>();

void key_callback(GLFWwindow* window, int key, int, int action, int) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {
    SceneConfig config {
        .lightSource = {
            .color = glm::vec4(1.0f),
            .ambientCoefficient = 0.1f,
            .diffuseCoeefficient = 0.8f,
            .specularCoefficient = 0.5f,
        },
    }; // Maybe we need construcor?

    const uint32_t screen_width = 800u;
    const uint32_t screen_heigth = 600u;
    const uint32_t screen_split_x = 350u;
    const uint32_t model_view_width = screen_width - screen_split_x;
    const uint32_t model_view_heigth = screen_heigth;
    const float model_aspect_ratio = (float)model_view_width / model_view_heigth; 

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(screen_width, screen_heigth, "Scene for lighting", NULL, NULL);
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
    Shader shaderTexture("shaders/default.vs", "shaders/texture.fs"); // TODO: add diffuse light and specular light
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

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos, ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(screen_split_x, viewport->WorkSize.y), ImGuiCond_Always);
    
        gui(config, model);

        glViewport(screen_split_x, 0u, model_view_width, model_view_heigth);

        auto aa = (0.5f * glfwGetTime());
        a = PI/4.0f + PI/4.0f * sin(aa);
        camera.pos.x = r * glm::cos(a);
        camera.pos.z = r * glm::sin(a);
        camera.dir.x = -camera.pos.x;
        camera.dir.z = -camera.pos.z;

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderTexture.use();
        shaderTexture.setMat4("view", camera.getView());
        shaderTexture.setMat4("perspective", glm::perspective( glm::radians(45.0f), model_aspect_ratio, 0.1f, 100.0f));
        shaderDiffuseColor.use();
        shaderDiffuseColor.setMat4("view", camera.getView());
        shaderDiffuseColor.setMat4("perspective", glm::perspective( glm::radians(45.0f), model_aspect_ratio, 0.1f, 100.0f));
        shaderLightSource.use();
        shaderLightSource.setMat4("view", camera.getView());
        shaderLightSource.setMat4("perspective", glm::perspective( glm::radians(45.0f), model_aspect_ratio, 0.1f, 100.0f));

        // Scene objects
        for (auto &[name, meshInstance]: model.meshInstances) {
            uint32_t meshIdx = meshInstance.idx;
            const Mesh &mesh = model.meshes[meshIdx];
            const Material &material = model.materials[mesh.materialIdx];
            if (material.type == MaterialType::Texture) {
                shaderTexture.use();
                shaderTexture.setMat4("model", meshInstance.transform);
                shaderTexture.setFloat("ambientCoefficient", config.lightSource.ambientCoefficient);
                shaderTexture.setFloat("diffuseCoeefficient", config.lightSource.diffuseCoeefficient);
                shaderTexture.setFloat("specularCoefficient", config.lightSource.specularCoefficient);
                shaderTexture.setVec3("lightSourceColor", config.lightSource.color);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, material.textureId);
                shaderTexture.setInt("textureId", 0);
            } else {
                shaderDiffuseColor.use();
                shaderDiffuseColor.setVec3("ambientCol", glm::vec3(material.diffuse));
                shaderDiffuseColor.setFloat("ambientCoefficient", config.lightSource.ambientCoefficient);
                shaderDiffuseColor.setFloat("diffuseCoeefficient", config.lightSource.diffuseCoeefficient);
                shaderDiffuseColor.setFloat("specularCoefficient", config.lightSource.specularCoefficient);
                shaderDiffuseColor.setMat4("model", meshInstance.transform);
                shaderDiffuseColor.setVec3("diffuseCol", glm::vec3(material.diffuse));
                shaderDiffuseColor.setVec3("lightSourceLoc", config.lightSource.position);
                shaderDiffuseColor.setVec3("lightSourceColor", config.lightSource.color);
                shaderDiffuseColor.setVec3("viewPos", camera.pos);
                shaderDiffuseColor.setInt("shininess", material.shininess);
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
