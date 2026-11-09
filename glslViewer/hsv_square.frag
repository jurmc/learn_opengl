uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / u_resolution;

    vec3 color = hsb2rgb(vec3(uv.x, 1.0, uv.y));
    
    gl_FragColor = vec4(color, 1.0);
}
