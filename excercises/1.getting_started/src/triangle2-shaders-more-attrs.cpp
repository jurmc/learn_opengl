#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include <math.h>

#include<iostream>

const char *vsSource = "                                  \n"
    "#version 330 core                                    \n"
    "layout (location = 0) in vec3 aPos;                  \n"
    "layout (location = 1) in vec3 aColor;                \n"
    "out float col;                                       \n"
    "void main()                                          \n"
    "{                                                    \n"
    "    gl_Position = vec4(aPos, 1.0);                   \n"
    "    col = aColor.r;                                       \n"
    "}                                                    \n";

const char *fsSource1 = "\n"
    "#version 330 core                             \n"
    "out vec4 FragColor;                           \n"
    "in float col;                                       \n"
    "                                              \n"
    "void main() {                                 \n"
    "    FragColor = vec4(col, 0.0, 0.5, 1.0);       \n"
    "}                                             \n";

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void) {
    std::cout << "Hello OpenGL!" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    int nAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttributes);
    std::cout << "Max vertex attributes: " << nAttributes << std::endl;

    float vertices[] = {
        0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f};

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs1);
    glLinkProgram(shaderProgram);
    glGetProgramiv(vs, GL_LINK_STATUS, &rc);
    if (!rc) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // draw triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // handle events, and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
