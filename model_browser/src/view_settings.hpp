#pragma once

#include "imgui.h"

enum class DisplayMethod { Wireframe, Solid };

struct ViewSettings {
    DisplayMethod mDisplayMethod = DisplayMethod::Solid;
    ImVec4 mLightColor{1.0f, 1.0f, 1.0f, 1.0f};
    float mLightStrength = 1.0f;
};

