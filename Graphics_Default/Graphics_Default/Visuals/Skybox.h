#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H

//Includes:
#include"../Visuals/Substances/SmartMaterial.h"

/// <summary>A skybox is a cube that uses all three dimensions of space to wrap six textures around the background of an environment.</summary>
class Skybox : public Substance
{
public:
	//Enums:
	enum CubeFace{TOP, BOTTOM, LEFT, RIGHT, BACK, FRONT, LENGTH};
	enum UniformNames { SKYBOX, PROJECTION, VIEW, NUM_UNIFORMS };
	GLuint uniforms[NUM_UNIFORMS];

	//Attributes:
	Texture* cubemap;

	//Constructor:
	Skybox();

	//Destructor:
	~Skybox();

	//Base methods;
	bool Load(const std::string location);
	void Update(Transform& transform);
	void Bind();
	void SetFace(CubeFace position, std::string location);
}; 
#endif // !SKYBOX_H