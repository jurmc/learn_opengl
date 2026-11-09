#define PI 3.1415926535

uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

varying vec2    v_texcoord;

mat2 scale(float s) {
    return mat2(s, 0.0, 0.0, s);
}

mat2 rotate(float angle) {
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}

float box(vec2 in_uv, vec2 size) {
    size = vec2(0.5) - size*0.5;
    vec2 out_uv = smoothstep(size, size+vec2(0.001), in_uv);
    out_uv *= smoothstep(size, size+vec2(0.001), vec2(1.0)+ - in_uv);
    return out_uv.x * out_uv.y;
}

float cross(vec2 in_uv, float size) {
    float shape = box(in_uv, vec2(size, size/4.0));
    shape += box(in_uv, vec2(size/4.0, size));
    return shape;
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv.x *= u_resolution.x/u_resolution.y;

    // Rotate & Scale
    uv -= 0.5;
    uv *= scale(sin(0.3*u_time));
    uv *= rotate(PI*sin(u_time));
    uv += 0.5;

    // Translate
    vec2 translate = vec2(cos(u_time), sin(u_time));
    uv += translate*0.15;


    vec3 color = vec3(uv.x, uv.y, uv.x * uv.y);

    float shape = cross(uv, 0.25);
    color += vec3(shape);
    
    gl_FragColor = vec4(color, 1.0);
}
