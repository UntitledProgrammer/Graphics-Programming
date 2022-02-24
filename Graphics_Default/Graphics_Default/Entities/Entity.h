#pragma once
#ifndef ENTITY_H
#define ENTITY_H

//Includes:
#include"../Components/MeshRenderer.h"
#include"../Shaders/SmartMaterial.h"

/// <summary>An entity is a simulated object that must always maintain the use of a mesh and mesh-renderer meaning it is visually simulated.</summary>
class Entity : public Simulated
{
public:
	//Attributes:
	MeshRenderer* meshRenderer;

	//Constructor:
	Entity();

	//Destructor:
	~Entity();

	//Methods:
	void Update();
	/// <summary>Removes the object from the simulated environment.</summary>
	void Dismantle();
	Simulated* Instantiate() override;

	//Properties:
	void SetMesh(Mesh* mesh);
	void SetMaterial(Substance* material);
};
#endif ENTITY_H