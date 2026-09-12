#include "imgui.h"

#include <assimp/scene.h>

#include <GLFW/glfw3.h>

class Gui {
public:
    Gui(GLFWwindow *w);

    void guiModelProperties(const aiScene *scene, double angle);

private:
    GLFWwindow *mWindow;
    ImGuiIO *mIo;
};


