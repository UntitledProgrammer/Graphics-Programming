#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

//Defines:
#define Resources ResourceManager::Instance()
#define Simulatables ResourceManager::Instance()->sims
#define Textures ResourceManager::Instance()->textures

//Includes:
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<glm.hpp>
#include<map>

#include"../Math/Vertex.h"
#include"../Visuals/Shader.h"
#include"../Components/Texture.h"
#include"../Math/Mesh.h"
#include"Resource.h"
#include"../Entities/EntityManager.h"

/// <summary>The resource manager is a singleton class that keeps track of all relevant resources required to run this project.</summary>
class ResourceManager
{
private:
	//Attributes:
	std::map<std::string, Shader*> shaders;

	//Static attributes:
	static ResourceManager* defaultInstance;

public:
	//Attributes:
	Resource<Simulated*> simulatables;
	SimulatedManager sims;
	Resource<Texture*> textures;

	//Constructor:
	ResourceManager();

	//Destructor:
	~ResourceManager();

	//Methods:
	Shader* GetShader(std::string location);
	template<typename Key, typename Type> bool Exists(std::map<Key, Type>* map, Key key) { return map->find(key) != map->end() ? true : false; }
	void UpdateSimulated();
	void InitaliseSimulated() { for (int i = 0; i < Simulatables.Size(); i++) { Simulatables.At(i)->Initialise(); } }

	//Static methods:
	static ResourceManager* Instance();
	static std::vector<Vertex> LoadMesh(std::string filelocation, std::string ambiant, std::string diffuse, std::string spec, std::string normal, std::vector<unsigned int>& indices);
	static void LoadMaterial(const std::string& MatLibLoc, std::string& ambiantLoc, std::string& diffLoc, std::string& specLoc, std::string& normalLoc);
};
#endif //!RESOURCE_MANAGER_H