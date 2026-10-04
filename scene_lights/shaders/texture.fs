#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform float ambientColComponent;

uniform sampler2D textureId;
uniform float diffuseColComponent;
uniform vec4 lightSourceColor;

void main() {
    vec4 ambient = ambientColComponent * texture(textureId, TexCoord);
    vec4 diffuse = diffuseColComponent * texture(textureId, TexCoord);
    FragColor = lightSourceColor * (ambient + diffuse);
}
