uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

float Square(vec2 uv, vec2 center, vec2 size, float blur) {
    float left = center.x - size.x/2.;
    float right = center.x + size.x/2.;
    float bottom = center.y - size.y/2.;
    float top = center.y + size.y/2.;
    float v;

    v = smoothstep(left-blur, left+blur, uv.x) * smoothstep(right+blur, right-blur, uv.x);
    v *= smoothstep(bottom-blur, bottom+blur, uv.y) * smoothstep(top+blur, top-blur, uv.y);

    return v;
}

float Linear(vec2 p1, vec2 p2, float in_val) {
    float a = (p2.y-p1.y) / (p2.x-p1.x);
    float b = p1.y - a * p1.x;

    float out_val = -a*in_val+b;
    return out_val;
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv -= .5;
    float x = uv.x;
    float y = uv.y;

    float xmin = -.3;
    float xmax = .3;

    float a = (.2-.01) / (xmax-xmin);
    float b = 0.01 - a * xmin;
    float blur = Linear(vec2(xmin, 0.01), vec2(xmax, 0.2), x);

    y += 0.1*sin(8.*x+4.*u_time);

    vec2 size = vec2(xmax-xmin, .1);
    float left_h = size.y;
    float right_h = .5*(1.+sin(u_time));
    size.y = Linear(vec2(xmin, left_h), vec2(xmax, right_h), uv.x);
    float sqaure = Square(vec2(x, y), vec2(0., 0.), size, blur);

    float d1 = (1.-abs(uv.y-y)) * sqaure;

    vec4 color = vec4(vec3(d1, 0.3*d1, sqaure*(1.-d1)), 1.);

    gl_FragColor = color;
}
