#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

//Includes:
#include"Shader.h"
#include"../Components/Texture.h"

class Material
{
private:
	//Attributes:
	glm::vec4 colour;
	Shader* shader;
	Texture* base;
	Texture* normal;
public:
	//Constructor:
	Material();

	//Destructor:
	~Material();

	//Methods:
	void SetBase(Texture* texture);
	void SetNormal(Texture* texture);
	void SetShader(Shader* shader);
	void Update();

	//Friends:
	friend class MeshRenderer;
};
#endif // !MATERIAL_H