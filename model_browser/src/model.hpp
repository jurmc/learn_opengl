#include "shader.hpp"
#include "mesh.hpp"
#include "texture.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include<string>
#include<vector>
#include<map>

class Model {
public:
    Model(const std::string &filename, const Shader &shader);

    // TODO: return some cheap (const) references instead of copies
    const aiScene *getAiScene() { return mScene; };

    void Draw(const Shader &s);

private:
    std::vector<Mesh> mMeshes;
    std::map<unsigned int, Texture> mTextures;
    std::string mFilename;
    Assimp::Importer mImporter;
    const aiScene *mScene;
};

