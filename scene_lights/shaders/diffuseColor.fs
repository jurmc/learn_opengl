#version 330 core

out vec4 FragColor;

uniform float ambientColComponent;
uniform vec4 ambientCol;

uniform float diffuseColComponent;
uniform vec4 diffuseCol;

uniform vec4 lightSourceColor;

void main() {
    vec4 ambient  = ambientColComponent * ambientCol;
    vec4 diffuse = diffuseColComponent * diffuseCol;
    FragColor = lightSourceColor * (ambient + diffuse);
}
