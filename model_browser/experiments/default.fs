#version 330 core

in vec3 vColor;
in vec2 vTex;

out vec4 FragColor;

uniform sampler2D ourTexture;

void main() {
    vec4 t = texture(ourTexture, vTex);
    FragColor = 0.5 * vec4(vColor, 1.0f) + 0.5 * vec4(t.x, t.y, t.z, 1.0f);
}
