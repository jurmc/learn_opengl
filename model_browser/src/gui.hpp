#pragma once

#include "view_settings.hpp"

#include "imgui.h"

#include <assimp/scene.h>

#include <GLFW/glfw3.h>

class Gui {
public:
    Gui(GLFWwindow *w);

    void ViewSettings();
    void GuiModelProperties(const aiScene *scene);

public:
    struct ViewSettings mViewSettings;

private:
    GLFWwindow *mWindow;
    ImGuiIO *mIo;
};


