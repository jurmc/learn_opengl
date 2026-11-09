uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

#define PI 3.1415926535
#define BORDER 0.05

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv.x = fract(uv.x * 2.0 + 2.0 * sin(2.0*PI*uv.x));
    uv.y = fract(uv.y * 2.1);

    vec2 bl = step(BORDER, uv);
    vec2 tr = step(BORDER, 1.0 - uv);
    float col = bl.x * bl.y * tr.x * tr.y;

    gl_FragColor = vec4(vec3(col), 1.0);
}
