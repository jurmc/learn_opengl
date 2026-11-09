const float PI = 3.141592654;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

const float sq_size = 40.0;

void main(void) {
    vec2 coord = gl_FragCoord.xy;
    float d_norm = 1.0 - distance(coord, u_mouse) / u_resolution.x;

    if (   coord.x < (u_mouse.x+sq_size) && coord.x > (u_mouse.x-sq_size)
        && coord.y < (u_mouse.y+sq_size) && coord.y > (u_mouse.y-sq_size)) {
        //gl_FragColor = vec4(sin(u_time), cos(u_time), 0.4, 1.0);
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else {
        //gl_FragColor = vec4(sin(u_time), d_norm/2.0, d_norm, 1.0);
        gl_FragColor = vec4(abs(sin(1.3*u_time)), 0.0, abs(sin(u_time+PI/4.0)), 1.0);
    }
}
