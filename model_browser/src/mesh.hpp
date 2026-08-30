#include "shader.hpp"

using Vertices = std::vector<float>;
using Indices = std::vector<unsigned int>;
using Meshes = std::vector<std::tuple<Vertices, Indices>>;

#include <vector>

class Mesh {
    public:
        Mesh(std::tuple<Vertices, Indices> &tuple);
        void Draw(const Shader &shader);

    private:
        std::vector<std::tuple<unsigned int, size_t>> mVaosAndIndicesNums; // TODO: will become vector of actual Mesh class
};

