const float PI = 3.1415926535;

uniform float u_time;
uniform vec2 u_resolution;

float Axes(vec2 uv) {
    const float w = 0.005/2.;
    float axes = smoothstep(0.-w, 0., uv.x) - smoothstep(0., w, uv.x);
    axes += smoothstep(0.-w, 0., uv.y) - smoothstep(0., w, uv.y);
    axes = clamp(axes, 0., 1.);
    return axes;
}

float Plot(vec2 uv, float amplitue, float phase, float freq) {
    float plot = 0.;
    float y = sin(phase + freq * uv.x);
    float d = abs(amplitue*y - uv.y);
    if (d < .01) plot = 1.0;
    return plot;
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    vec2 span = vec2(4. * PI, 2.1);
    uv.xy *= span;
    uv -= span/2.;

    vec3 col = vec3(1., 1., 0.);

    float amplitue = 1.;
    float freq = 1.;
    float phase = u_time;

    float sine_plot = Plot(uv, amplitue, phase, freq);
    col *= sine_plot;

    float a = Axes(uv);
    if (a > 0.) col = vec3(a);
    
    gl_FragColor = vec4(col, 1.);
}
