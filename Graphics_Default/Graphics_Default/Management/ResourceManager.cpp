#include "ResourceManager.h"
ResourceManager* ResourceManager::defaultInstance = 0;


ResourceManager::ResourceManager() {};

ResourceManager::~ResourceManager() {};

ResourceManager* ResourceManager::Instance()
{
	if (!defaultInstance) defaultInstance = new ResourceManager();
	return defaultInstance;
}

std::vector<Vertex> ResourceManager::LoadOBJ(std::string folderLocation, std::string filename, std::string ambiant, std::string diffuse, std::string spec, std::string normal, std::vector<glm::uint>& indicies)
{
	//Defines:
	std::string line;
	std::string MatLibName;
	std::string meshName;
	//Vectors:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> coordinates;
	std::vector<Vertex> verticies;

	//Open the file:
	std::ifstream file;
	std::string location = folderLocation + "/" + filename;
	file.open(location.c_str(), std::ifstream::in);

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			if (line[0] == '#') continue; //If line is commented out, do not to process it.
			//Defines:
			std::string FirstWord = line.substr(0, line.find(' '));

			if (FirstWord == "mtllib")
			{
				MatLibName = line.substr(line.find(' ') + 1, line.find('\n'));
			}
			else if (FirstWord == "o") //Object name.
			{
				meshName = line.substr(line.find(' '), line.find('\n'));
			}
			else if (FirstWord == "v") //Vert pos.
			{
				std::string values = line.substr(line.find(' '), line.find('\n'));
				glm::vec3 pos = glm::vec3(0);
				sscanf_s(values.c_str(), "%f %f %f", &pos.x, &pos.y, &pos.z);
				positions.push_back(pos);
			}
			else if (FirstWord == "vn") //Vert normals.
			{
				std::string values = line.substr(line.find(' '), line.find('\n'));
				glm::vec3 pos = glm::vec3(0);
				sscanf_s(values.c_str(), "%f %f %f", &pos.x, &pos.y, &pos.z);
				coordinates.push_back(pos);
			}
			else if (FirstWord == "usemtl") 
			{
				meshName = line.substr(line.find(' '), line.find('\n'));
				//LoadMaterial();
			}
			else if (FirstWord == "f")
			{
				std::string values = line.substr(line.find(' '), line.find('\n'));
				Vertex vertsInFace[3];
				unsigned int TmpPosition[3], TmpTexCoords[3], TmpNormals[3];

				sscanf_s(values.c_str(), " %d/%d/%d %d/d/%d %d/%d/%d", &TmpPosition[0], &TmpTexCoords[0], &TmpNormals[0],
					&TmpPosition[1], &TmpTexCoords[1], &TmpNormals[1],
					&TmpPosition[2], &TmpTexCoords[2], &TmpNormals[2]
					);

				vertsInFace[0].position = positions[TmpPosition[0] - 1];
				//vertsInFace[0]. = coordinates[TmpTexCoords[0] - 1];
				//vertsInFace[0].n= normals[TmpNormals[0] - 1];

			}
		}
	}
	else std::cerr << "Unable to load text file: " << location.c_str() << std::endl;


	return std::vector<Vertex>();
}

Shader* ResourceManager::GetShader(std::string location)
{
	//Add additional check to make sure shader was loaded correctly.

	if (!Exists<std::string, Shader*>(&shaders, location)) { shaders.emplace(std::make_pair(location, new Shader(location))); }
	return shaders[location];
}

Texture* ResourceManager::GetTexture(std::string location)
{
	if (!Exists<std::string, Shader*>(&shaders, location))
	{
		Texture* texture = new Texture();
		if (texture->Load(location)) { textures.emplace(std::make_pair(location, texture)); }
		else std::cerr << "Unable to load texture: " << location.c_str() << std::endl;
	}

	return textures[location];
}