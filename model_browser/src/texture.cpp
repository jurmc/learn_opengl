#include "texture.hpp"

#include <glad/glad.h>

#include <stb/stb_image.h>

Texture::Texture(const char* filePath) : mGPUId{} {
    int w, h, nCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imgBuff = stbi_load(filePath, &w, &h, &nCh, 3);

    glGenTextures(1, &mGPUId);
    glBindTexture(GL_TEXTURE_2D, mGPUId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, imgBuff);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(imgBuff);
}

