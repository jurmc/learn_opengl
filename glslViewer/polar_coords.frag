uniform vec2 u_resolution;
uniform float u_time;

float plot(float v, float pct) {
    return smoothstep(pct - 0.01, pct, v) - smoothstep(pct, pct + 0.01, v);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv = (uv - 0.5) * 2.0;
    uv.x *= u_resolution.x / u_resolution.y;

    float r = length(uv);
    float a = atan(uv.y, uv.x) + 0.2 * u_time;

    //float p = 0.5 + 0.4 * sin(3.0 * a);
    //float p = 0.7 + 0.2 * sin(12.0 * a);
    //float p = 0.7 + 0.2 * abs(sin(12.0 * a));
    float p = 0.7 + 0.1 * smoothstep(0.5, 1.0, abs(sin(12.0 * a)));
    float c = plot(p, r);
    
    gl_FragColor = vec4(vec3(c), 1.0);
}
