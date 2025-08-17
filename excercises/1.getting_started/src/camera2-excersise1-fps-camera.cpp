#include "shader.h"
#include "learnopengl/camera-fps.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

Camera_Movement processKeyboard(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        return Camera_Movement::LEFT;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        return Camera_Movement::RIGHT;
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        return Camera_Movement::FORWARD;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        return Camera_Movement::BACKWARD;
    }

    return Camera_Movement::NONE;
}

// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
Camera camera(cameraPos);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

double prev_mouse_xpos, prev_mouse_ypos;
double mouse_xmove, mouse_ymove;
double pitch = 0.0f;
double yaw = -90.0f;

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    static bool initialized = false;
    double mouse_xmove, mouse_ymove;

    if (!initialized) {
        initialized = true;
        mouse_xmove = xpos;
        mouse_ymove = ypos;
    }

    mouse_xmove = xpos - prev_mouse_xpos ;
    mouse_ymove = prev_mouse_ypos - ypos;
    prev_mouse_xpos = xpos;
    prev_mouse_ypos = ypos;

    float sensitivity = 0.05f;
    yaw += sensitivity * mouse_xmove;
    pitch += sensitivity * mouse_ymove;
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    camera.ProcessMouseMovement(mouse_xmove, mouse_ymove);
}

void zoom_callback(GLFWwindow *window, double xoffset, double yoffset) {
    std::cout << "zoom_callback yoffset: " << yoffset << std::endl;
    camera.ProcessMouseScroll(yoffset); // TODO:
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, zoom_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
         //  coords         // texture coords
         -0.5f, -0.5f, -0.5,  0.0f, 0.0f,
          0.5f, -0.5f, -0.5,  1.0f, 0.0f,
          0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
          0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

         -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
          0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
          0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
          0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
         -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

         -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
         -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

          0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
          0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
          0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
          0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
          0.5f,  0.5f,  0.5f, 1.0f, 0.0f,

         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
          0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
          0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
          0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

         -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
          0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
          0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
          0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f, 0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("shaders/camera2-using-camera-class.vs", "shaders/camera2-using-camera-class.fs");

    int width, height, nChannels;
    // Image and textture
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Cannot load image" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char *data2 = stbi_load("textures/awesomeface.png", &width, &height, &nChannels, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Cannot load image" << std::endl;
    }
    stbi_image_free(data2);

    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    glm::vec3 cubePositions[] = {
        glm::vec3(  0.0f,   0.0f,   0.0f),
        glm::vec3(  2.0f,   5.0f, -15.0f),
        glm::vec3( -1.5f,  -2.2f,  -2.5f),
        glm::vec3( -3.8f,  -2.0f, -12.3f),
        glm::vec3(  2.4f,  -0.4f,  -3.5f),
        glm::vec3( -1.7f,   3.0f,  -7.5f),
        glm::vec3(  1.3f,  -2.0f,  -2.5f),
        glm::vec3(  1.5f,   2.0f,  -2.5f),
        glm::vec3(  1.5f,   0.2f,  -1.5f),
        glm::vec3( -1.3f,   1.0f,  -1.5f)
    };

    float aspect_ratio = 800.0f / 600.0f;

    float deltaTime;
    float lastFrame;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        float deltaTime = glfwGetTime() - lastFrame;
        float lastFrame = currentFrame;

        // input & camera
        camera.ProcessKeyboard(processKeyboard(window), deltaTime);
        glm::mat4 view = camera.GetViewMatrix();
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        // render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader.use();

        for (unsigned int i = 1; i < 10; ++i)
        {

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspect_ratio, 0.1f, 100.0f);
            int projectionLoc = glGetUniformLocation(shader.ID, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            if ( i % 3 == 0) {
                model = glm::rotate(model, glm::radians(20.0f + (float)glfwGetTime() * i * 6), glm::vec3(0.5f, 1.0f, 0.0f));
                int modelLoc = glGetUniformLocation(shader.ID, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            } else {
                model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(0.5f, 1.0f, 0.0f));
                int modelLoc = glGetUniformLocation(shader.ID, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            }

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 5);
        }

        // hanlde events, and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    return 0;
}

