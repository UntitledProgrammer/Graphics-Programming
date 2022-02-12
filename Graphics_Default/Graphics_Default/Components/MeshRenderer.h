#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

//Includes:
#include"Mesh.h"
#include"../Shaders/Material.h"
#include"../Management/ResourceManager.h"

class MeshRenderer
{
private:
	//Attributes:
	Mesh* mesh;
	Material* material;
public:
	//Constructor:
	MeshRenderer();

	//Destructor:
	~MeshRenderer();

	//Methods:
	bool LoadMesh(std::string location);
	bool LoadMaterial(std::string location);
	void ApplyMaterial(Material* material);
	void ApplyMesh(Mesh* mesh);
};
#endif //!MESH_RENDERER_H