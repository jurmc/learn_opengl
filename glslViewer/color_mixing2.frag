uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

#define PI 3.1415926535

vec3 colorA = vec3(0.149,0.141,0.912);
vec3 colorB = vec3(1.000,0.833,0.224);

float plot(vec2 p, float pct) {
    return smoothstep(pct-.01, pct, p.y) - smoothstep(pct, pct+0.01, p.y);
}


void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;

    vec3 color = vec3(.0);
    vec3 pct = vec3(uv.x);

    pct.r = smoothstep(0.0, 1.0, uv.x)+0.2;
    //pct.g = sin(PI * uv.x);
    //pct.b = pow(uv.x, 2.0);

    color = mix(colorA, colorB, pct);

    // Plot transition lines for each channel
    color = mix(color, vec3(1.0, 0.0, 0.0), plot(uv, pct.r));
    color = mix(color, vec3(0.0, 1.0, 0.0), plot(uv, pct.g));
    color = mix(color, vec3(0.0, 0.0, 1.0), plot(uv, pct.b));

    gl_FragColor = vec4(vec3(color), 1.0);
}
