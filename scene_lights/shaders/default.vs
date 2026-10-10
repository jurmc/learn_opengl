#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
uniform vec3 cameraPos;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{

    gl_Position = perspective * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));

    Normal = aNormal;
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);


}
