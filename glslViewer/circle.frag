const float PI = 3.141592654;

uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 u_mouse;

mat2 rot(float angle) {
    float c = cos(angle);
    float s = sin(angle);

    mat2 r = mat2(c, -s, s, c);
    return r;
}

float plot(vec2 r, vec2 st, float width) {
    float elipse = pow(st.x/r.x, 2.0) + pow(st.y/r.y, 2.0) - 1.0;
    return smoothstep(width, 0.00, abs(elipse));
}

float combine_plots(vec2 st, float width) {
    float p = 0.0;
    for (float rx = 0.05; rx <= 0.40; rx = rx + 0.05) {
        for (float ry = 0.40 - rx; ry >= 0.05; ry = ry - 0.05) {
            p = p + plot(vec2(rx, ry), st, width);
        }
    }

    return p;
}

void main(void) {
    vec2 st = gl_FragCoord.xy / u_resolution - 0.5;
    vec2 st_mouse = u_mouse.xy / u_resolution - 0.5;
    float t = u_time;
    st = st * rot(t);
    st_mouse = st_mouse * rot(t);
    float d = distance(st, st_mouse);

    float p = combine_plots(st, d/5.0);
    gl_FragColor = vec4(vec3(p), 1.0);
}
