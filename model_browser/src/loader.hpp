#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include<string>
#include<vector>

using Vertices = std::vector<float>;
using Indices = std::vector<unsigned int>;
using Meshes = std::vector<std::tuple<Vertices, Indices>>;

class Loader {
public:
    Loader(const std::string &filename);

    // TODO: return some cheap (const) references instead of copies
    const aiScene *getAiScene() { return mScene; };
    Meshes getMeshes() { return mMeshes; };

private:
    std::string mFilename;
    Assimp::Importer mImporter;
    const aiScene *mScene;
    Meshes mMeshes;
};

