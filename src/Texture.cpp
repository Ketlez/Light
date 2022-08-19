#include "Texture.h"

Texture::Texture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

void Texture::setData(int internalFormat, int dataFormat, int channelFormat, int width, int height, void* data)
{
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, channelFormat, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

void Texture::activeTexture(int textureId)
{
    glActiveTexture(GL_TEXTURE0 + textureId);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
