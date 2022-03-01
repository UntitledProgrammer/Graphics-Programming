#include "ResourceManager.h"
ResourceManager* ResourceManager::defaultInstance = 0;


ResourceManager::ResourceManager() {};

ResourceManager::~ResourceManager() {};

ResourceManager* ResourceManager::Instance()
{
	if (!defaultInstance) defaultInstance = new ResourceManager();
	return defaultInstance;
}

std::vector<Vertex> ResourceManager::LoadMesh(std::string filelocation, std::string ambiant, std::string diffuse, std::string spec, std::string normal, std::vector<unsigned int>& indices)
{
	//Defines:
	std::string line;
	std::string MatLibName;
	std::string meshName;
	//Vectors:
	std::vector<glm::vec3> VertPositions;
	std::vector<glm::vec3> VertNormals;
	std::vector<glm::vec3> VertTextureCoords;
	std::vector<Vertex> FinalVerts;

	//Open the file:
	std::ifstream file;
	file.open(filelocation.c_str(), std::ifstream::in);

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
				float x, y, z;
				sscanf_s(values.c_str(), "%f %f %f", &x, &y, &z);
				VertPositions.push_back(glm::vec3(x,y,z));
			}
			else if (FirstWord == "vn") //Vert normals.
			{
				std::string values = line.substr(line.find(' '), line.find('\n'));
				float x, y, z;
				sscanf_s(values.c_str(), "%f %f %f", &x, &y, &z);
				VertNormals.push_back(glm::vec3(x,y,z));
			}
			else if (FirstWord == "vt") //Texture coordinates.
			{
				std::string values = line.substr(line.find(' '), line.find('\n'));
				float x, y, z;
				sscanf_s(values.c_str(), "%f %f %f", &x, &y, &z);
				VertTextureCoords.push_back(glm::vec3(x,y,z));
			}

			else if (FirstWord == "usemtl") 
			{
				meshName = line.substr(line.find(' '), line.find('\n'));
				//LoadMaterial();
			}

			else if (FirstWord == "f")
			{
				std::string FaceValues = line.substr(line.find(' '), line.find('\n'));
				Vertex vertsInFace[3];
				unsigned int TmpPosition[3], TmpTexCoords[3], TmpNormals[3];

				sscanf_s(FaceValues.c_str(), " %d/%d/%d %d/%d/%d %d/%d/%d", 
					&TmpPosition[0], &TmpTexCoords[0], &TmpNormals[0],
					&TmpPosition[1], &TmpTexCoords[1], &TmpNormals[1],
					&TmpPosition[2], &TmpTexCoords[2], &TmpNormals[2]
					);

				vertsInFace[0].position = VertPositions[TmpPosition[0] - 1];
				vertsInFace[0].uv = VertTextureCoords[TmpTexCoords[0] - 1];
				vertsInFace[0].normal = VertNormals[TmpNormals[0] - 1];

				vertsInFace[1].position = VertPositions[TmpPosition[1] - 1];
				vertsInFace[1].uv = VertTextureCoords[TmpTexCoords[1] - 1];
				vertsInFace[1].normal = VertNormals[TmpNormals[1] - 1];

				vertsInFace[2].position = VertPositions[TmpPosition[2] - 1];
				vertsInFace[2].uv = VertTextureCoords[TmpTexCoords[2] - 1];
				vertsInFace[2].normal = VertNormals[TmpNormals[2] - 1];

				FinalVerts.push_back(vertsInFace[0]);
				FinalVerts.push_back(vertsInFace[1]);
				FinalVerts.push_back(vertsInFace[2]);
			}

		}
		for (int i = 0; i < FinalVerts.size(); i++)
		{
			indices.push_back(i);
		}
		return FinalVerts;
	}
	else std::cerr << "Unable to load text file: " << filelocation.c_str() << std::endl;
	return std::vector<Vertex>();
}

void ResourceManager::LoadMaterial(const std::string& MatLibLoc, std::string& ambiantLoc, std::string& diffLoc, std::string& specLoc, std::string& normalLoc)
{
	std::ifstream file;
	const char* fileNameChar = MatLibLoc.c_str();
	file.open(fileNameChar, std::ifstream::in);
	std::string line;
	std::string MatName;

	if (file.is_open())
	{
		while (file.good())
		{
			std::getline(file, line);
			if (line[0] != '#')
			{
				std::string firstWord = line.substr(0, line.find(' '));
				if (std::strstr(firstWord.c_str(), "newmtl")) //Material.
				{
					MatName = line.substr(line.find(' ') + 1, line.find('\n'));
				}
				else if (std::strstr(firstWord.c_str(), "map_Ka")) //Ambient.
				{
					ambiantLoc = line.substr(line.find(' ') + 1, line.find('\n'));
				}
				else if (std::strstr(firstWord.c_str(), "map_Ks")) //Specular.
				{
					specLoc = line.substr(line.find(' ') + 1, line.find('\n'));
				}
				else if (std::strstr(firstWord.c_str(), "map_bump")) //Normal map.
				{
					normalLoc = line.substr(line.find(' ') + 1, line.find('\n'));
				}
			}
		}
	}
	else
	{
		std::cerr << "Unable to load text file: " << MatLibLoc << std::endl;
	}
	file.close();
}

Shader* ResourceManager::GetShader(std::string location)
{
	//Add additional check to make sure shader was loaded correctly.

	if (!Exists<std::string, Shader*>(&shaders, location)) { shaders.emplace(std::make_pair(location, new Shader(location))); }
	return shaders[location];
}


void ResourceManager::UpdateSimulated()
{
	for (int i = 0; i < Simulatables.Size(); i++)
	{
		Simulatables.At(i)->Update();
	}
}
