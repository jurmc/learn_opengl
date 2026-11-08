#define SOKOL_IMPL
#define SOKOL_GLCORE

#include "vecmath.h"

#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_hello.glsl.h"

#include "GLFW/glfw3.h"
#include "glfw/glfw_glue.h"

int main(void) {
    glfw_init(&(glfw_desc_t){
            .title = "hello sokol (glfw)",
            .width = 640,
            .height = 480,
            .no_depth_buffer = true,
            });
    sg_setup(&(sg_desc){
            .environment = glfw_environment(),
            .logger = slog_func,
            });

    const float vertices[] = {
        // Postion              // Color
        -0.5f, -0.5f, 0.5f,      1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,      0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.5f,      0.0f, 0.0f, 1.0f, 1.0f,
    };
    sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
            .data = SG_RANGE(vertices),
            });

    sg_shader shd = sg_make_shader(triangle_shader_desc(sg_query_backend()));

    sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc){
            .shader = shd,
            .layout = {
                .attrs = {
                    [0].format = SG_VERTEXFORMAT_FLOAT3,
                    [1].format = SG_VERTEXFORMAT_FLOAT4,
                }}});

    sg_bindings bind = {
        .vertex_buffers[0] = vbuf,
    };


    sg_pass_action action = {
        .colors[0] = {
            .load_action = SG_LOADACTION_CLEAR,
            .clear_value = {0.0f, 0.0f, 0.0f, 1.0f},
        }
    };

    vs_params_t vs_uniforms;
    fs_params_t fs_uniforms;

    while (!glfwWindowShouldClose(glfw_window())) {
        float time = glfwGetTime();

        sg_begin_pass(&(sg_pass){
                .action = action,
                .swapchain = glfw_swapchain() });

        sg_apply_pipeline(pip);
        sg_apply_bindings(&bind);

        mat44_t model_rot = mat44_rotation_yaw_pitch_roll(0.7*time, 1.0*time, 0.0f);
        vs_uniforms.model = model_rot;
        sg_apply_uniforms(UB_vs_params, &SG_RANGE(vs_uniforms));
        fs_uniforms.time = time;
        sg_apply_uniforms(UB_fs_params, &SG_RANGE(fs_uniforms));

        sg_draw(0, 3, 1);
        sg_end_pass();
        sg_commit();
        glfwSwapBuffers(glfw_window());
        glfwPollEvents();
    }

    sg_shutdown();
    glfwTerminate();

    return 0;
}
