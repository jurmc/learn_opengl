#pragma once

#include "shader.hpp"
#include "view_settings.hpp"

using Vertices = std::vector<float>;
using Indices = std::vector<unsigned int>;

#include <vector>

class Mesh {
    public:
        Mesh(Vertices vertices, Indices indices, unsigned int GPUTextureId); // TODO: typle here is overkill
        void Draw(const Shader &shader, const ViewSettings &viewSettings);

    private:
        GLuint mVao;
        GLsizei mIdxCnt;
        unsigned int mGPUTextureId;
};

