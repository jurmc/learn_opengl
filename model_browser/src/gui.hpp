#include "imgui.h"

#include <assimp/scene.h>

class Gui {
public:
    Gui();   

    void guiModelProperties(const aiScene *scene, double angle);

private:
    ImGuiIO& mIo;
};


