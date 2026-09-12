#include "imgui.h"

#include <assimp/scene.h>

#include <GLFW/glfw3.h>

enum class DisplayMethod { Wireframe, Solid };

struct ViewSettings {
    DisplayMethod mDisplayMethod = DisplayMethod::Solid;
    ImVec4 mLightColor{1.0f, 1.0f, 1.0f, 1.0f};
    float mLightStrength = 1.0f;
};

class Gui {
public:
    Gui(GLFWwindow *w);

    void ViewSettings();
    void GuiModelProperties(const aiScene *scene, double angle);

public:
    struct ViewSettings mViewSettings;

private:
    GLFWwindow *mWindow;
    ImGuiIO *mIo;
};


