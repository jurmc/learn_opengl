#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>

const char *vsSource = "                                  \n"
    "#version 330 core                                    \n"
    "layout (location = 0) in vec3 aPos;                  \n"
    "void main()                                          \n"
    "{                                                    \n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
    "}                                                    \n";

const char *fsSource1 = "\n"
    "#version 330 core                             \n"
    "out vec4 FragColor;                           \n"
    "                                              \n"
    "void main() {                                 \n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
    "}                                             \n";

const char *fsSource2 = "\n"
    "#version 330 core                             \n"
    "out vec4 FragColor;                           \n"
    "                                              \n"
    "void main() {                                 \n"
    "    FragColor = vec4(1.0f, 1.0f, 0.2f, 1.0f); \n"
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

    float vertices1[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f};

    float vertices2[] = {
        0.45f,  0.5f, 0.0f,
        -0.55f, 0.5f, 0.0f,
        -0.55f, -0.5f, 0.0f};

    unsigned int indices[] = {
        0, 1, 2, // first triangle
        3, 0, 2, // second triangle
    };

    unsigned int VAO1;
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    unsigned int VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

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

    unsigned int fs2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs2, 1, &fsSource2, NULL);
    glCompileShader(fs2);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &rc);
    if (!rc) {
        glGetShaderInfoLog(fs2, 512, NULL, infoLog);
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

    unsigned int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vs);
    glAttachShader(shaderProgram2, fs2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(vs, GL_LINK_STATUS, &rc);
    if (!rc) {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs1);
    glDeleteShader(fs2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 1st triangle
        glUseProgram(shaderProgram1);
        glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 2nd triangle
        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // hanlde events, and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
