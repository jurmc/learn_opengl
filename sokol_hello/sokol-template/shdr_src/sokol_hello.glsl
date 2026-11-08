@ctype mat4 mat44_t

@vs vs

layout(binding=0) uniform vs_params {
    mat4 model;
};

in vec4 position;
in vec4 color0;

out vec4 color;

void main() {
    gl_Position = model * position;
    color = color0;
}
@end

@fs fs

layout(binding=1) uniform fs_params {
    float time;
};

in vec4 color;
out vec4 frag_color;

void main() {
    float strength = 0.5 + 0.5*sin(time);
    frag_color = color * strength;
}
@end

@program triangle vs fs
