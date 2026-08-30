#include "main.hpp"
#include "loader.hpp"
#include "gui.hpp"
#include "shader.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<iostream>
#include<vector>
#include<map>
#include<print>


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

static void glfw_error_callback(int error, const char* description)
{
    std::println(stderr, "GLFW Error %d: %s\n", error, description);
}

int main_browser(void) {
    std::cout << "Model Browser, hello!" << std::endl;

    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = nullptr;
    ImGui_ImplOpenGL3_Init(glsl_version);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    int nAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttributes);
    std::cout << "Max vertex attributes: " << nAttributes << std::endl;

    Loader loader("../kenney_car-kit/Models/GLB format/cone.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/debris-bolt.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/debris-door.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/kart-oobi.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/tractor.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/cube.glb");
    //Loader loader("test");

    Shader shader("shaders/default.vs", "shaders/default.fs");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(3);

    Gui gui;
    double angle;

    while (!glfwWindowShouldClose(window)) {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        angle = 6.0f * glfwGetTime();
        gui.guiModelProperties(loader.getAiScene(), angle); // TODO: maybe here we,'ll pass const Model instead of aiScene?
        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shader.setMat4("model", model);

        // Rendering
        ImGui::Render();
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        processInput(window);
        loader.Draw(shader); // TODO: ultimately this won't be call to loader, but loader will return model, and here we call Draw on Mode
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // hanlde events, and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
    }

    // ImGui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // GLFW cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
