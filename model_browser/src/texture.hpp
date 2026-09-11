class Texture {
    public:
        Texture(const char* filePath); 

        unsigned int getGPUId() {return mGPUId;};
       
    private:
        unsigned int mGPUId;
};
