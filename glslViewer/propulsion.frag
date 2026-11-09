const float PI = 3.1415926535;

uniform vec2 u_resolution;
uniform float u_time;

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv -= vec2(.2, 0.2);
    float a = -PI/4.;
    float c = cos(a);
    float s = sin(a);
    mat2 rot = mat2(c, -s, s, c);
    uv *= rot;

    float l = length(uv);
    float coma_w = 0.04 + 0.01*sin(20.*u_time) + 0.005*sin(30.*u_time) + 0.002*sin(50.*u_time);
    float color = smoothstep(uv.x+coma_w/2., uv.x-coma_w/2., l);

    gl_FragColor = vec4(vec3(color), 1.);
}
