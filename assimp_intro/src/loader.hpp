#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include<string>
#include<vector>
#include<print>

class Loader {
public:
    Loader(const std::string &filename);

    const aiScene *getAiScene() { return mScene; };
    std::vector<float> getVertices() {return mVertices;};

private:
    std::string mFilename;
    Assimp::Importer mImporter;
    const aiScene *mScene;
    std::vector<float> mVertices;
};
