#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform float ambientColComponent;
uniform vec4 ambientCol;

uniform float diffuseColComponent;
uniform vec4 diffuseCol;

uniform vec3 lightSourceLoc;
uniform vec4 lightSourceColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightSourceLoc - FragPos);
    float lightDiffused = max(dot(norm, lightDir), 0.0f);

    vec4 ambient  = ambientColComponent * ambientCol;
    vec4 diffuse = lightDiffused * diffuseCol;
    FragColor = lightSourceColor * (ambient + diffuse);
}
