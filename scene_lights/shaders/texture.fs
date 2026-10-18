#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform float ambientCoefficient;

uniform sampler2D textureId;
uniform float diffuseCoeefficient;
uniform vec3 lightSourceColor;

void main() {
    vec3 ambient = vec3(ambientCoefficient * texture(textureId, TexCoord));
    vec3 diffuse = vec3(diffuseCoeefficient * texture(textureId, TexCoord));
    FragColor = vec4(lightSourceColor * (ambient + diffuse), 0.0f);
}
