#pragma once
#ifndef SMART_MATERIAL_H
#define SMART_MATERIAL_H
//Includes:
#include<iostream>
#include<string>
#include<glew.h>
#include<glm.hpp>
#include<fstream>
#include"../Components/Texture.h"
#include"../Math/Transform.h"
#include"../Simulated/Camera.h"
#include"../Simulated/LightBase.h"

class Substance
{
protected:
	//Attributes:
	enum Types { VERTEX, FRAGMENT, SHADER_TYPES };
	std::string name;
	GLuint program;
	GLuint shaders[SHADER_TYPES];
public:
	//Attributes:
	glm::vec4 colour;

	//Abstract methods:
	virtual bool Load(const std::string location) = 0;
	virtual void Update(Transform& transform, Light& light) = 0;
	virtual void Bind() = 0;

	//Virtual methods:
	virtual void Delete();

	//Static methods:
	static GLuint CreateShader(const std::string& source, GLenum type);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string& filename);

};
#endif // !SMART_MATERIAL_H