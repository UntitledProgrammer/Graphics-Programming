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

class ResourceManager
{
	//Attributes:


public:
	//Constructor:
	ResourceManager();

	//Destructor:
	~ResourceManager();

	//Methods:

	//Static methods:
	static std::vector<Vertex> LoadOBJ(std::string folderLocation, std::string filename, std::string ambiant, std::string diffuse, std::string spec, std::string normal, std::vector<glm::uint>& indicies);
};
#endif //!RESOURCE_MANAGER_H