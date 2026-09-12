#version 330 core

in vec2 vUvCoords;
in float vDist;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec4 lightColor;
uniform float lightStrength;

void main() {
    vec4 t  = texture(ourTexture, vUvCoords);
    FragColor = vec4(t.x, t.y, t.z, 1.0f) * lightColor * lightStrength * vDist;
}
