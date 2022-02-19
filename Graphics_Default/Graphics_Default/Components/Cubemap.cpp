#include "Cubemap.h"

Cubemap::Cubemap()
{

}

Cubemap::~Cubemap()
{
}

bool Cubemap::Load(std::string location)
{

	return false;
}

bool Cubemap::LoadMap(std::vector<std::string> files)
{
	//A cube map must have six textures that correspond to a face.
	if (files.size() != 6) return false;

	//Generate and bind texture to 'ID' object.
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	//Load faces of cube.
	int channels;
	for (unsigned int i = 0; i < files.size(); i++)
	{
		data = stbi_load(files[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Error: Failed to load file at path: " << files[i] << std::endl;
			return false;
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	return true;
}

void Cubemap::Update()
{
}

void Cubemap::Bind(std::string name, GLuint program, int index)
{
}