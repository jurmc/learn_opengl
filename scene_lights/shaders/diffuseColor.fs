#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform float ambientCoefficient;
uniform vec3 ambientCol;

uniform float diffuseCoeefficient; // TODO: typo
uniform vec3 diffuseCol;

uniform float specularCoefficient;

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
    float spec = pow(max(dot(viewDir, lightReflected), 0.0), shininess);

    vec3 ambient  = ambientCoefficient * ambientCol;
    vec3 diffuse = lightDiffused * diffuseCol;
    vec3 specular = specularCoefficient * spec * lightSourceColor;

    vec3 result = (ambient + diffuse + specular) * diffuseCol;
    FragColor = vec4(result, 1.0f);
}
