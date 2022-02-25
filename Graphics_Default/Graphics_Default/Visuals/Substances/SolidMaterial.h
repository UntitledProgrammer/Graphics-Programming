#pragma once
#ifndef SOLID_MATERIAL_H
#define SOLID_MATERIAL_H

//Includes:
#include"../Visuals/Substances/SmartMaterial.h"

/// <summary>A solid material is a type of material providing a single, solid colour for visualising a mesh.</summary>
class SolidMaterial : public Substance
{
	//Attributes:
	enum UniformNames { MODEL_U, PROJECTION_U, VIEW_U, FRAG_LIGHTCOLOUR, FRAG_LIGHTPOS, FRAG_CAMERAPOS, FORWARD, SURFACE_COLOUR, NUM_UNIFORMS };
	GLuint uniforms[NUM_UNIFORMS];
public:
	//Constructor:
	SolidMaterial();

	//Destructor:
	~SolidMaterial();

	//Base methods:
	bool Load(const std::string location);
	void Update(Transform& transform);
	void Bind();
};
#endif // !SOLID_MATERIAL_H