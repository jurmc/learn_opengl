@vs vs

in vec4 position;
in vec4 color0;

out vec4 color;

void main() {
    gl_Position = position;
    color = color0;
}
@end

@fs fs

layout(binding=0) uniform fs_params {
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
