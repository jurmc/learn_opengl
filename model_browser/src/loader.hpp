#include "shader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include<string>
#include<vector>
#include<tuple>

using Vertices = std::vector<float>;
using Indices = std::vector<unsigned int>;
using Meshes = std::vector<std::tuple<Vertices, Indices>>;

class Loader {
public:
    Loader(const std::string &filename);

    // TODO: return some cheap (const) references instead of copies
    const aiScene *getAiScene() { return mScene; };

    // This part will become part of interface of Model and Mesh later, and this Loader class will be returning Model (containing Meshes)
    void ProsessMesh(std::tuple<Vertices, Indices> &tuple);
    void Draw(const Shader &s);
    std::vector<std::tuple<unsigned int, size_t>> mVaosAndIndicesNums; // TODO: will become vector of actual Mesh class

private:
    std::string mFilename;
    Assimp::Importer mImporter;
    const aiScene *mScene;
    Meshes mMeshes;
};

