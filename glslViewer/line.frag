uniform vec2 u_resolution;
uniform float u_time;

float plot(vec2 st, float pct) {
    return smoothstep(pct - 0.02, pct, st.y) - smoothstep(pct, pct + 0.02, st.y); 
}

void main(void) {
    vec2 st = gl_FragCoord.xy / u_resolution;
    float y = exp(st.x)-0.5;
    float ct = 0.5+0.4*sin(u_time);
    float width = 0.5+0.5*sin(u_time);
    float v = smoothstep(ct-width/2.0, ct+width/2.0, st.x);

    //float col_strength = 0.55+0.3*sin(u_time);
    float col_strength = 1.0;
    vec3 color = v*vec3(col_strength);
    gl_FragColor = vec4(color, 1.0);
}
