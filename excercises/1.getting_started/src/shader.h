#pragma once

#include <glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

// TODO: get rid of this static strings
const char *vsSourceLoc = "                                  \n"
    "#version 330 core                                    \n"
    "layout (location = 0) in vec3 aPos;                  \n"
    "void main()                                          \n"
    "{                                                    \n"
    "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
    "}                                                    \n";

const char *fsSourceLoc = "\n"
    "#version 330 core                                    \n"
    "out vec4 FragColor;                                  \n"
    "uniform float vertexColor;                            \n"
    "                                                     \n"
    "void main() {                                        \n"
    "    FragColor = vec4(0.0f, vertexColor, 0.0f, 1.0f); \n"
    "}                                                    \n";

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    void setBool(const char* name, bool val) const;
    void setInt(const char* name, int val) const;
    void setFloat(const char* name, float val) const;
};

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderStream.rdbuf();

        fShaderFile.close();
        vShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = vShaderStream.str();
    } catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NO_SUCCESSFULLY_read" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSourceLoc, NULL);
    glCompileShader(vs);

    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX:COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSourceLoc, NULL);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX:COMPILATION_FAILED\n" <<
            infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vs);
    glAttachShader(ID, fs);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const char* name, bool val) const {
    glUniform1i(glGetUniformLocation(ID, name), val);
}

void Shader::setInt(const char* name, int val) const {
    glUniform1i(glGetUniformLocation(ID, name), val);
}

void Shader::setFloat(const char* name, float val) const {
    glUniform1f(glGetUniformLocation(ID, name), val);
}
