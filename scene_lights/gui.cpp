#include "mesh.hpp"
#include "model.hpp"
#include "config.hpp"

#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <string>
#include <map>

const ImGuiWindowFlags window_flags = 
  ImGuiWindowFlags_NoMove | 
  ImGuiWindowFlags_NoResize | 
  ImGuiWindowFlags_NoCollapse | 
  ImGuiWindowFlags_NoSavedSettings;

static void guiLights(SceneConfig &config);
static void guiObjects(Model& model);

void gui(SceneConfig& config, Model& model)
{
    ImGui::Begin("Light scene for Learn OpenGL", nullptr, window_flags);
    {
        auto flags = ImGuiTreeNodeFlags_DefaultOpen;
        if (ImGui::TreeNodeEx("Lighting", flags)) {
            guiLights(config);
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Objects", flags)) {
            guiObjects(model);
            ImGui::TreePop();
        }
    }
    ImGui::End();
}

static void guiLights(SceneConfig &config) {
    auto lsCol = &config.lightSource.color;
    float color[3] = {lsCol->x, lsCol->y, lsCol->z};
    if (ImGui::ColorEdit3("Light color", (float*)&color)) {
        lsCol->x = color[0];
        lsCol->y = color[1];
        lsCol->z = color[2];
    }
    ImGui::InputFloat("Ambient coefficient", &config.lightSource.ambientCoefficient);
    ImGui::InputFloat("Diffuse coefficient", &config.lightSource.diffuseCoeefficient);
    ImGui::InputFloat("Specular coefficient", &config.lightSource.specularCoefficient);
    auto lsPos = &config.lightSource.position;
    float pos[3]{lsPos->x, lsPos->y, lsPos->z};
    if (ImGui::InputFloat3("Camera pos", pos)) {
        lsPos->x = pos[0];
        lsPos->y = pos[1];
        lsPos->z = pos[2];
        glm::mat4 lightModel = glm::mat4(1.0f); // TODO: duplicated code
        lightModel = glm::translate(lightModel, config.lightSource.position);
        auto SCALE = 0.25f;
        lightModel = glm::scale(lightModel, glm::vec3(SCALE));
        config.lightSource.transform = lightModel;
    }
}

static void guiObjects(Model& model) {
    std::map<std::string, MeshInstance>& meshInstances = model.meshInstances;
    std::vector<Mesh>& meshes = model.meshes;
    std::vector<Material>& materials = model.materials;

    static bool initialized = false;
    static std::map<uint32_t, std::string> idxMap;
    if (!initialized) {
        int idx = 0;
        for (auto &[key, val] : meshInstances) {
            idxMap[idx] = key;
            ++idx;
        }
        initialized = true;
    }

    static uint32_t selected_idx = 0;
    if (ImGui::BeginCombo("Objects", idxMap[selected_idx].c_str())) {
        for (auto &[key, val] : idxMap) {
            bool is_selected = (selected_idx == key);
            if (ImGui::Selectable(val.c_str(), is_selected)) {
                selected_idx = key;
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    MeshInstance& mInstance = meshInstances[idxMap[selected_idx]];
    Mesh& mesh = meshes[mInstance.idx];
    Material& material = materials[mesh.materialIdx];
    if (mesh.hasTexture) {
        ImGui::SeparatorText("Textured");
        ImGui::LabelText("File name:", "TODO, so far this is hardcoded, should be taken from GLB file");
    } else {
        ImGui::SeparatorText("Non textured");
        glm::vec4& d = material.diffuse;
        float col[4] = {d.x, d.y, d.z, d.w};
        if (ImGui::ColorEdit4("Diffuse", col)) {
            d.x = col[0]; d.y = col[1]; d.z = col[2]; d.w = col[3];
        }
    }

    ImGui::InputFloat("Shininess", &material.shininess); // TODO: change shininess so it uses set of predefined values: const char* items[] = {"2", "4", "8", "16", "32", "64", "128", "256"};
}
    

