uniform vec2 u_resolution;
uniform float u_time;

#define PI 3.1415926535

vec3 palette(float v) {
    vec3 a = vec3( 0.408, 0.178, 0.500);
    vec3 b = vec3(-0.382, 0.500, 0.500);
    vec3 c = vec3(-0.542, 0.333, 0.500);
    vec3 d = vec3(-0.072, 0.667, 0.500);

    return a + b*cos(2.0*PI*c*v + d);
}

void main() {
    vec2 uv = gl_FragCoord.xy / u_resolution;
    uv.x *= u_resolution.x / u_resolution.y;
    uv.x *= 2.47;
    uv.y *= 2.24;
    uv.x -= 2.0;
    uv.y -= 1.12;

    // Rotation
    float s = sin(u_time);
    float c = cos(u_time);
    mat2 rot_m = mat2(c, -s, s, c);
    uv *= rot_m;

    // Zoom
    float zoom = 1.0 * sin(0.23 * u_time);
    uv *= zoom;

    // Center orbit
    uv.x += cos(0.1 * u_time);
    uv.y += cos(PI+ 0.15 * u_time);


    float r = 0.0;
    float i = 0.0;
    int max_iteration = 100;

    int it = 0;
    while (pow(r, 2.0) + pow(i, 2.0) < 2.0 && it < max_iteration) {
        float r_temp = pow(r, 2.0) - pow(i, 2.0) + uv.x;
        i = 2.0 * r * i + uv.y;
        r = r_temp;
        it += 1;
    }

    vec3 color = vec3(0.0);
    if ( max_iteration != it) {
        color = palette(float(it) / float(max_iteration));
    }

    gl_FragColor = vec4(color, 1.0);
}
