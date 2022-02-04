#include "Texture.h"

Texture::Texture()
{
    width = 0; height = 0; format = 0; data = 0; id = 0;
}

Texture::~Texture()
{

}

bool Texture::load(std::string location)
{
    int componentsMagnitude = 0;
    data = stbi_load(location.c_str(), &width, &height, &componentsMagnitude, STBI_rgb_alpha);

    if (data == NULL) std::cerr << "Texture loading failed for texture: " << location << std::endl;

    switch(componentsMagnitude)
    {
    case 1:
        format = GL_RED;
    case 3:
        format = GL_RGB;
    case 4:
        format = GL_RGBA;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return false;
}

void Texture::update()
{
    glBindTexture(GL_TEXTURE_2D, id);
}