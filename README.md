WAYLAND_DISPLAY=wayland-1 LIBGL_ALWAYS_SOFTWARE=1 ./main
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
shader: MESA_SHADER_FRAGMENT
source_blake3: {0xc27636b0, 0xea0fb650, 0x57a2259f, 0x83b3d390, 0x7adb2d15, 0xa7375b7b, 0x39618af8, 0x1e117cb9}
name: GLSL3
next_stage: MESA_SHADER_FRAGMENT
outputs_written: 4
subgroup_size: 1
first_ubo_is_default_ubo: true
flrp_lowered: true
outputs: 1
decl_var shader_out INTERP_MODE_NONE none highp vec4 FragColor (FRAG_RESULT_DATA0.xyzw, 0, 0)
decl_function main () (entrypoint)

impl main {
    block b0:   // preds:
    32     %0 = @decl_reg (num_components=4, num_array_elems=0, bit_size=32, divergent=1)
    32     %1 = load_const (0x3f800000 = 1.000000 = 1065353216)
    32     %2 = load_const (0x3f800000 = 1.000000 = 1065353216)
    32     %3 = load_const (0x3e4ccccd = 0.200000 = 1045220557)
    32     %4 = load_const (0x3f800000 = 1.000000 = 1065353216)
    32x4   %5 = mov %1 (0x3f800000).xxxx
                @store_reg (%5, %0) (base=0, wrmask=x, legacy_fsat=0)
    32x4   %6 = mov %2 (0x3f800000).xxxx
                @store_reg (%6, %0) (base=0, wrmask=y, legacy_fsat=0)
    32x4   %7 = mov %3 (0x3e4ccccd).xxxx
                @store_reg (%7, %0) (base=0, wrmask=z, legacy_fsat=0)
    32x4   %8 = mov %4 (0x3f800000).xxxx
                @store_reg (%8, %0) (base=0, wrmask=w, legacy_fsat=0)
    32     %9 = deref_var &FragColor (shader_out vec4)
    32x4  %10 = @load_reg (%0) (base=0, legacy_fabs=0, legacy_fneg=0)
                @store_deref (%9, %10) (wrmask=xyzw, access=none)
                // succs: b1
    block b1:
}

shader: MESA_SHADER_FRAGMENT
source_blake3: {0xc27636b0, 0xea0fb650, 0x57a2259f, 0x83b3d390, 0x7adb2d15, 0xa7375b7b, 0x39618af8, 0x1e117cb9}
name: GLSL3
next_stage: MESA_SHADER_FRAGMENT
outputs_written: 4
subgroup_size: 1
first_ubo_is_default_ubo: true
flrp_lowered: true
outputs: 1
decl_var shader_out INTERP_MODE_NONE none highp vec4 FragColor (FRAG_RESULT_DATA0.xyzw, 0, 0)
decl_function main () (entrypoint)

impl main {
    block b0:   // preds:
    32     %0 = @decl_reg (num_components=4, num_array_elems=0, bit_size=32, divergent=1)
    32     %1 = load_const (0x3f800000 = 1.000000 = 1065353216)
    32     %2 = load_const (0x3f800000 = 1.000000 = 1065353216)
    32     %3 = load_const (0x3e4ccccd = 0.200000 = 1045220557)
    32     %4 = load_const (0x3f800000 = 1.000000 = 1065353216)
    32x4   %5 = mov %1 (0x3f800000).xxxx
                @store_reg (%5, %0) (base=0, wrmask=x, legacy_fsat=0)
    32x4   %6 = mov %2 (0x3f800000).xxxx
                @store_reg (%6, %0) (base=0, wrmask=y, legacy_fsat=0)
    32x4   %7 = mov %3 (0x3e4ccccd).xxxx
                @store_reg (%7, %0) (base=0, wrmask=z, legacy_fsat=0)
    32x4   %8 = mov %4 (0x3f800000).xxxx
                @store_reg (%8, %0) (base=0, wrmask=w, legacy_fsat=0)
    32     %9 = deref_var &FragColor (shader_out vec4)
    32x4  %10 = @load_reg (%0) (base=0, legacy_fabs=0, legacy_fneg=0)
                @store_deref (%9, %10) (wrmask=xyzw, access=none)
                // succs: b1
    block b1:
}

Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
Hello OpenGL!
