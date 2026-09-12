#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUvCoords;

uniform mat4 model;

out vec2 vUvCoords;
out float vDist;

void main()
{
    vec3 lightLoc = vec3(1.0f);
    float lightDist = length(lightLoc - aPos);
    if (lightDist > 1.0f) {
        lightDist = 1.0f;
    } else if (lightDist < 0.1f) {
        lightDist = 0.1f;
    }

    gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    vUvCoords = aUvCoords; 
    vDist = lightDist;
}
