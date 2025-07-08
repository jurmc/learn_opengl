#version 330 core

out vec4 FragColor;

uniform float vertexColor;

void main() {
    FragColor = vec4(0.0f, vertexColor, 0.0f, 1.0f);
}
