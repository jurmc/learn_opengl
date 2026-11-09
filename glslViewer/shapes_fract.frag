uniform vec2 u_resolution;
uniform float u_time;

#define PI 3.1415926535

vec3 color(float v) {
    vec3 a = vec3(0.5, 0.1, 0.3);
    vec3 b = vec3(0.1, 0.2, 0.5);
    vec3 c = vec3(3.0, 6.0, 1.0);
    vec3 d = vec3(0.1, 2.0, 0.5);

    return a + b*cos(2.0*PI*c*v + d);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv = (uv.xy - 0.5) * 2.0;
    float shift = fract(0.3 - 0.1 * u_time);
    float shift2 = 0.3;

    //float l = length(abs(uv) - shift);
    //float l = length(min(abs(uv) - shift2, 0.0));
    float l = length(max(abs(uv) - shift2, 0.0));

    vec3 c = color(l - 0.1 * u_time);
    //vec3 c = color(l);
    gl_FragColor = vec4(fract(c*10.0), 1.0);
}
