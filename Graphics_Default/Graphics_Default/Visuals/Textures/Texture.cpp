#include "Texture.h"

Texture::Texture()
{
    width = 0; height = 0; format = 0; data = 0; id = 0;
}

Texture::~Texture()
{

}



GLuint Texture::getTexture(std::string location)
{
    GLuint textureID;
    int width, height, componentsMagnitude = 0;

    unsigned char* data = stbi_load(location.c_str(), &width, &height, &componentsMagnitude, STBI_rgb_alpha);

    if (data == NULL) std::cerr << "Texture loading failed for texture: " << location << std::endl;
    GLenum format;
    switch (componentsMagnitude)
    {
    case 1:
        format = GL_RED;
    case 3:
        format = GL_RGB;
    case 4:
        format = GL_RGBA;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    return textureID;
}


bool Texture::Load(std::string location)
{
    int componentsMagnitude = 0;

    data = stbi_load(location.c_str(), &width, &height, &componentsMagnitude, STBI_rgb_alpha);

    if (data == NULL) { std::cerr << "Texture loading failed for texture: " << location << std::endl; return false; }

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

    return true;
}

void Texture::LoadCubemap(std::vector<std::string> faces)
{
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int width, height, channels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* texture = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);
        if (texture) //If texture is not null / loaded.
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X +i, 0, GL_RGB, width, height, 0, GL_RGB,  GL_UNSIGNED_BYTE, texture);
            stbi_image_free(texture);
        }
        else
        {
            std::cerr << "Error: Failed to load cubemap textures at path: " << faces[i] << std::endl;
            stbi_image_free(texture);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::Update()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Bind(std::string name, GLuint program, int index)
{
    //glActiveTexture(GL_TEXTURE0);
    GLuint textureLoc = glGetUniformLocation(program, name.c_str());
    glUniform1i(textureLoc, 0);
    glBindTexture(GL_TEXTURE_2D, id);
}