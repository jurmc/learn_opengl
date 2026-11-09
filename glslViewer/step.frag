uniform vec2 u_resolution;
uniform float u_time;

#define PI 3.1415926535

vec3 WhiteCol = vec3(1.0, 1.0, 1.0);
vec3 RedCol = vec3(1.0, 0.0, 0.0);

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution; 
    uv -= 0.5;
    uv.y = sin(2.0 * PI *uv.x);

    vec3 color = mix(RedCol, WhiteCol, vec3(step(0.0, uv.y)));
    gl_FragColor = vec4(color, 1.0);
}
