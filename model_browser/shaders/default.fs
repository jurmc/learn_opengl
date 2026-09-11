#version 330 core

in vec2 vUvCoords;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main() {
    vec4 t  = texture(ourTexture, vUvCoords);
    FragColor = vec4(t.x, t.y, t.z, 1.0f);
}
