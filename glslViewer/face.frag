const float PI = 3.1415926535;

uniform vec2 u_resolution;
uniform float u_time;

float Circle(vec2 uv, vec2 center, float r) {
    float l = distance(uv, center);
    float w = r / 50.0;
    float circle = smoothstep(r+w/2., r-w/2., l);

    return circle;
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    uv -= .5;
    float a = u_time;
    float c = cos(a);
    float s = sin(a);
    mat2 rotation = mat2(c, -s, s, c);
    uv = uv * rotation;

    float face = Circle(uv, vec2(.0, .0), 0.4);
    face -= Circle(uv, vec2(-.15, .15), 0.05);
    face -= Circle(uv, vec2(+.15, .15), 0.05);

    vec2 mouth_pos = vec2(.0, -.0);
    float mouth = Circle(uv, mouth_pos, 0.3);
    mouth -= Circle(uv, vec2(mouth_pos.x, mouth_pos.y+0.1), 0.3);
    mouth = clamp(mouth, 0., 1.);

    face -= mouth;
   
    vec3 yellow = vec3(1., 1., 0.);
    vec3 color = face * yellow;
    gl_FragColor = vec4(color, 1.);
}
