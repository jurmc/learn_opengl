#include"shader.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <list>

void processInput(GLFWwindow *window, float *fov_angle,
        float *cam_x, float *cam_z) {
    float fov_angle_incr = 0.05;
    float aspect_ratio_incr = 0.05;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *fov_angle = *fov_angle + fov_angle_incr;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *fov_angle = *fov_angle - fov_angle_incr;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        ;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        ;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        *cam_x = *cam_x + 0.1;
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        *cam_x = *cam_x - 0.1;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        *cam_z = *cam_z + 0.1;
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        *cam_z = *cam_z - 0.1;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

    Shader shader("shaders/texture3-minecraft-cubes.vs", "shaders/texture3-minecraft-cubes.fs");

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
    unsigned char *data = stbi_load("/home/jurmc/game_assets/SBS - Sandbox Style Terrain - Texture Pack/Textures/Dirt/cubeDirt_1.png", &width, &height, &nChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Cannot load image" << std::endl;
    }
    stbi_image_free(data);

    shader.use();
    shader.setInt("texture1", 0);

    std::list<glm::vec3> cubePositions2 = {
       glm::vec3(  0.0f,   0.0f,   0.0f),
       glm::vec3(  2.0f,   0.0f,   0.0f),
       glm::vec3(  4.0f,   0.0f,   0.0f),
       glm::vec3(  6.0f,   0.0f,   0.0f)
    };

    float fov_angle = 45.0f;
    float aspect_ratio = 800.0f / 600.0f;
    float cam_x  = -5.0f;
    float cam_z = -10.0f;

    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window, &fov_angle,
                &cam_x, &cam_z);

        // render commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);

        shader.use();

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(cam_x, -1.0f, cam_z));
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 projection = glm::mat4(1.0f);

        for (glm::vec3 cube : cubePositions2)
        {
            projection = glm::perspective(glm::radians(fov_angle), aspect_ratio, 0.1f, 100.0f);
            int projectionLoc = glGetUniformLocation(shader.ID, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cube);

            model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            int modelLoc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 5);
        }

        // hanlde events, and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    return 0;
}

