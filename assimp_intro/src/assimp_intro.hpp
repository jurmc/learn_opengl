#include<string>
#include<vector>

std::vector<float> LoadModel(); // Temporary
std::vector<float> LoadModel2(); // Temporary

class Loader {
public:
    Loader(const std::string &filename);

    std::vector<float> getVertices() {return mVertices;};

private:
    std::string mFilename;
    std::vector<float> mVertices;
};
