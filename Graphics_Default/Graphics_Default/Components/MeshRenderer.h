#pragma once
#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

//Includes:
#include"../Math/Mesh.h"
#include"../Visuals/Substances/Material.h"
#include"../Management/ResourceManager.h"
#include"../Visuals/Substances/SmartMaterial.h"

/// <summary>A mesh-renderer is designed to handle the pipeline of processes required before a mesh can be output to a screen.</summary>
class MeshRenderer
{
private:
	//Attributes:
	Mesh* mesh;
	Substance* material;
public:
	//Attrubutes:
	bool shaded = true;
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
	void RenderShadows();

	//Friends:
	friend class Entity;
	friend class Animator;
};
#endif //!MESH_RENDERER_H