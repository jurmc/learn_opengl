uniform vec2    u_resolution;
uniform vec2    u_mouse;
uniform float   u_time;

#define PI 3.1415926535

vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main() {
    gl_FragColor = vec4(0.3, 0.4, 0.5, 1.0);
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv -= 0.5;
    uv *= 2.0;
    float ratio = u_resolution.x / u_resolution.y;
    uv.x *= ratio;

    float angle = 1.0 + atan(uv.y,uv.x)/(2.0*PI) + 0.1 * u_time;
    float dist = length(uv);

    vec3 color = hsb2rgb(vec3(angle, 1.0, dist));

    gl_FragColor = vec4(color, 1.0);

}
