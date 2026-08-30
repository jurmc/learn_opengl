#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use() const;

    void setBool(const char* name, bool val) const;
    void setInt(const char* name, int val) const;
    void setFloat(const char* name, float val) const;
    void setVec4(const char* name, glm::vec4 val) const;
    void setMat4(const char* name, glm::mat4 val) const;
};
