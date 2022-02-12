#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

//Includes:
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<glm.hpp>
#include<map>
#include"../Math/Vertex.h"
#include"../Shaders/Shader.h"
#include"../Components/Texture.h"

class ResourceManager
{
private:
	//Attributes:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Texture*> textures;

	//Static attributes:
	static ResourceManager* defaultInstance;

public:
	//Constructor:
	ResourceManager();

	//Destructor:
	~ResourceManager();

	//Methods:
	Shader* GetShader(std::string location);
	Texture* GetTexture(std::string location);
	template<typename Key, typename Type> bool Exists(std::map<Key, Type>* map, Key key) { return map->find(key) != map->end() ? true : false; }

	//Static methods:
	static ResourceManager* Instance();
	static std::vector<Vertex> LoadOBJ(std::string folderLocation, std::string filename, std::string ambiant, std::string diffuse, std::string spec, std::string normal, std::vector<glm::uint>& indicies);
};
#endif //!RESOURCE_MANAGER_H