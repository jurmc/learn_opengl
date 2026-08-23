#include "main.hpp"
#include "loader.hpp"
#include "gui.hpp"

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
#include<print>


const char *vsSource = "                                  \n"
    "#version 330 core                                    \n"
    "layout (location = 0) in vec3 aPos;                  \n"
    "uniform mat4 model;                                  \n"
    "void main()                                          \n"
    "{                                                    \n"
    "    gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
    "}                                                    \n";

const char *fsSource1 = "\n"
    "#version 330 core                             \n"
    "out vec4 FragColor;                           \n"
    "                                              \n"
    "void main() {                                 \n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
    "}                                             \n";

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

    //Loader loader("../kenney_car-kit/Models/GLB format/cone.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/debris-bolt.glb");
    //Loader loader("../kenney_car-kit/Models/GLB format/debris-door.glb");
    Loader loader("../kenney_car-kit/Models/GLB format/kart-oobi.glb");
    auto vertices = loader.getVertices();
    std::print("vertices.size(): {}\n", vertices.size());
    auto verticesNum = vertices.size();
    auto verticesSize = vertices.size() * sizeof(float);

    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);

    int rc;
    char infoLog[512];
    glGetShaderiv(vs, GL_COMPILE_STATUS, &rc);
    if (!rc) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    unsigned int fs1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs1, 1, &fsSource1, NULL);
    glCompileShader(fs1);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &rc);
    if (!rc) {
        glGetShaderInfoLog(fs1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    unsigned int shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vs);
    glAttachShader(shaderProgram1, fs1);
    glLinkProgram(shaderProgram1);
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &rc);
    if (!rc) {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glPointSize(5);

    Gui gui;
    double angle;

    while (!glfwWindowShouldClose(window)) {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        angle = 6.0f * glfwGetTime();
        gui.guiModelProperties(loader.getAiScene(), angle);
        auto model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        int modelLoc = glGetUniformLocation(shaderProgram1, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        // Rendering
        ImGui::Render();
        glClearColor(0.2, 0.2, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        // render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 1st triangle
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_POINTS, 0, verticesNum);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
