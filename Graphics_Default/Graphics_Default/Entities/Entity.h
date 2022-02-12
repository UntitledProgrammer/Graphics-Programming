#pragma once
#ifndef ENTITY_H
#define ENTITY_H

//Includes:
#include"../Components/MeshRenderer.h"

/// <summary>An entity is a simulated object that must always maintain the use of a mesh and mesh-renderer meaning it is visually simulated.</summary>
class Entity : Simulated
{
public:
	//Attributes:
	Transform transform;
	MeshRenderer* meshRenderer;

	//Constructor:
	Entity();

	//Destructor:
	~Entity();

	//Methods:
	void Update();
	/// <summary>Removes the object from the simulated environment.</summary>
	void Dismantle();
};
#endif ENTITY_H