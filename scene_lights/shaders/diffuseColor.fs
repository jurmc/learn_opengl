#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform float ambientColComponent;
uniform vec3 ambientCol;

uniform float diffuseColComponent;
uniform vec3 diffuseCol;

uniform vec3 lightSourceLoc;
uniform vec3 lightSourceColor;
uniform int shininess;

uniform vec3 viewPos;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightSourceLoc - FragPos);
    float lightDiffused = max(dot(norm, lightDir), 0.0f);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightReflected = reflect(-lightDir, norm);
    float specStrength = 0.5f;
    float spec = pow(max(dot(viewDir, lightReflected), 0.0), shininess);

    vec3 ambient  = ambientColComponent * ambientCol;
    vec3 diffuse = lightDiffused * diffuseCol;
    vec3 specular = specStrength * spec * lightSourceColor;

    vec3 result = (ambient + diffuse + specular) * diffuseCol;
    FragColor = vec4(result, 1.0f);
}
