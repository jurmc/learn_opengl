#include<string>

class MyImporter {
public:
    MyImporter(const std::string &filename) : filename(filename) {};
    ~MyImporter();

    bool Import() {return false;};

private:
    std::string filename;
};
