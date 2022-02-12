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
	Texture* base;
	Texture* normal;
public:
	//Constructor:
	Material();

	//Destructor:
	~Material();

	//Methods:

};
#endif // !MATERIAL_H