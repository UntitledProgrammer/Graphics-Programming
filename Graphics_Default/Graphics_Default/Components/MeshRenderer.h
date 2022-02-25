#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

//Includes:
#include"Mesh.h"
#include"../Visuals/Substances/Material.h"
#include"../Management/ResourceManager.h"
#include"../Visuals/Substances/SmartMaterial.h"

class MeshRenderer
{
private:
	//Attributes:
	Mesh* mesh;
	Substance* material;
public://Change to private, at later date.
	Transform* transform;
public:
	//Constructor:
	MeshRenderer();

	//Destructor:
	~MeshRenderer();

	//Methods:
	bool LoadMesh(std::string location);
	bool LoadMaterial(std::string location);
	void ApplyMaterial(Substance* material);
	void ApplyMesh(Mesh* mesh);
	void SetTransform(Transform* transform);
	void Render();

	//Friends:
	friend class Entity;
	friend class Animator;
};
#endif //!MESH_RENDERER_H