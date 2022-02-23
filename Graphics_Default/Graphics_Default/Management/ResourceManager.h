#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#define Resources ResourceManager::Instance()

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
#include"../Components/Mesh.h"

class ResourceManager
{
private:
	//Attributes:
	std::map<std::string, Shader*> shaders;
	std::map<std::string, Texture*> textures;

	//Static attributes:
	static ResourceManager* defaultInstance;

public:
	//Attributes:
	std::vector<Simulated*> simulatedBodies;

	//Constructor:
	ResourceManager();

	//Destructor:
	~ResourceManager();

	//Methods:
	void AddBody(Simulated* body) { simulatedBodies.push_back(body); }
	Shader* GetShader(std::string location);
	Texture* GetTexture(std::string location);
	template<typename Key, typename Type> bool Exists(std::map<Key, Type>* map, Key key) { return map->find(key) != map->end() ? true : false; }

	//Static methods:
	static ResourceManager* Instance();
	static Mesh* LoadMesh(std::string filelocation, std::string ambiant, std::string diffuse, std::string spec, std::string normal);
	static void LoadMaterial(const std::string& MatLibLoc, std::string& ambiantLoc, std::string& diffLoc, std::string& specLoc, std::string& normalLoc);
};
#endif //!RESOURCE_MANAGER_H