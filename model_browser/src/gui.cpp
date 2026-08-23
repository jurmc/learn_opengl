#include "gui.hpp"
#include "imgui.h"

#include <assimp/scene.h>

Gui::Gui() : mIo(ImGui::GetIO()) {
    mIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    mIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
}

void Gui::guiModelProperties(const aiScene *scene, double angle) {
    static float f = 0.0f;
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("Model file name: %s", "empty");
    ImGui::Text("aiScene->mName: %s", scene->mName.C_Str()); 
    ImGui::Text("mNumMeshes: %d", scene->mNumMeshes); 

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit floats representing a color

    ImGui::Text("Angle %.1f", angle);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / mIo.Framerate, mIo.Framerate);
    ImGui::End();
}
