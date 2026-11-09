uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

#define PI 3.1415926535

vec3 palette(float v) {
    vec3 a = vec3(0.5, 0.1, 0.3);
    vec3 b = vec3(0.1, 0.2, 0.5);
    vec3 c = vec3(3.0, 6.0, 1.0);
    vec3 d = vec3(0.1, 2.0, 0.5);

    return a + b*cos(2.0*PI*c*v + d);
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv.x *= u_resolution.x / u_resolution.y;
    uv = 2.0 * uv - 1.0;

    int N = 5;

    float angle = atan(uv.x, uv.y) + PI + u_time;
    float angular_w = 2.0*PI / float(N);

    float section = floor(.5 + angle / angular_w);
    float d = cos(section * angular_w - angle) * length(uv);

    float section_n = section / float(N);
    vec3 color = 1.0 - smoothstep(0.4, 0.41, d) * palette(section_n);

    gl_FragColor = vec4(color, 1.0);
}
