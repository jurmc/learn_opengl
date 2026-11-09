uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

#define PI 3.1415926535

#define A vec3(0.5, 0.5, 0.5)
#define B vec3(0.5, 0.5, 0.5)
#define C vec3(1.0, 1.0, 5.0)
#define D vec3(0.80, 0.90, 0.30)

varying vec2    v_texcoord;

void main(void) {
    vec4 color = vec4(vec3(0.0), 1.0);
    vec2 pixel = 1.0/u_resolution.xy;
    vec2 st = gl_FragCoord.xy * pixel;
    vec2 uv = v_texcoord;
    uv -= 0.5;

    float l = 2.0*length(uv);
    vec3 c = A + B * cos(2.0*PI*(C*l+D-u_time));
    c = 0.15*exp(3.0*c);
//    c = 1.0 - c;
    c *= 0.4;
    color.rgb = vec3(c);
    
    gl_FragColor = color;
}
