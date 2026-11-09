uniform vec2 u_resolution;
uniform float u_time;

#define MAX_D 0.9
#define MAX_R MAX_D/2.0
#define MIN_R 0.1

float circle_tweak(vec2 uv, float radius) {
    return smoothstep(radius-0.01, radius, dot(uv, uv)*4.0) - smoothstep(radius, radius+0.01, dot(uv, uv)*4.0);
}

float circle(vec2 uv, float radius) {
    float d = length(uv);
    return smoothstep(radius-0.01, radius, d) - smoothstep(radius, radius+0.01, d);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    float scale = (1.0 + 4.0*abs(cos(0.2*u_time)));
    uv = fract(uv * scale);
    uv -= 0.5;

    //float pct = distance(uv, vec2(0.4)) + distance(uv, vec2(0.6));
    //float pct = distance(uv, vec2(0.4)) * distance(uv, vec2(0.6));
    //float pct = min(distance(uv, vec2(0.4)), distance(uv, vec2(0.6)));
    //float pct = max(distance(uv, vec2(0.4)), distance(uv, vec2(0.6)));
    //float pct = pow(distance(uv, vec2(0.4)), distance(uv, vec2(0.6)));

    float r = MIN_R + abs((MAX_R-MIN_R) * sin(0.7*u_time));

    float pct = 0.0;
    //float r = 0.1 + 0.4 * abs(sin(0.5 * u_time));
    pct = circle_tweak(uv, r);
    pct += circle(uv, r);

    gl_FragColor = vec4(vec3(pct), 1.0);
}
