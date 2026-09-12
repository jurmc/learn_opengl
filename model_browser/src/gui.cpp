#include "gui.hpp"
#include "imgui.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <assimp/scene.h>

Gui::Gui(GLFWwindow *w)
    : mWindow(w)
{
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
         
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)
                                            //
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(mWindow, true);
    const char* glsl_version = nullptr;
    ImGui_ImplOpenGL3_Init(glsl_version);

    mIo = &ImGui::GetIO();
    mIo->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    mIo->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
}

void Gui::ViewSettings() {
    ImGui::Begin("View settings");

    if  (ImGui::TreeNode("Display method")) {
        if (ImGui::Selectable("Wireframe", mViewSettings.mDisplayMethod == DisplayMethod::Wireframe)) {
            mViewSettings.mDisplayMethod = DisplayMethod::Wireframe;
        }
        if (ImGui::Selectable("Solid", mViewSettings.mDisplayMethod == DisplayMethod::Solid)) {
            mViewSettings.mDisplayMethod = DisplayMethod::Solid;
        }
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Light")) {

        ImGui::ColorEdit3("Color", (float*)&mViewSettings.mLightColor);
        ImGui::SliderFloat("Strength", &mViewSettings.mLightStrength, 0.0f, 1.0f);            // Edit float using a slider from 0.0f to 1.0f

        ImGui::TreePop();
    }

    ImGui::End();
}

void Gui::GuiModelProperties(const aiScene *scene, double angle) {

    ImGui::Begin("Model properties");

    ImGui::Text("Model file name: %s", "empty");
    ImGui::Text("aiScene->mName: %s", scene->mName.C_Str()); 
    ImGui::Text("mNumMeshes: %d", scene->mNumMeshes); 
    for (size_t i = 0; i < scene->mNumMeshes; i++) {
        ImGui::Text("mesh[%zu] numFaces: %d", i, scene->mMeshes[i]->mNumFaces);
    }

    ImGui::Text("Angle %.1f", angle);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / mIo->Framerate, mIo->Framerate);
    ImGui::End();
}
