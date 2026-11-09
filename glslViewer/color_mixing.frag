uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

vec3 colorBlue = vec3(0.149,0.141,0.912);
vec3 colorYellow = vec3(1.000,0.833,0.224);

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;

    float pct = abs(sin(u_time));

    vec3 color = mix(colorBlue, colorYellow, pct);

    gl_FragColor = vec4(color, 1.0);
}
