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


/// <summary>
/// The substance class is a type of interface (base class) that provides the basic necessary functionality for using OpenGL shaders.
/// The class is designed to be expandable so that you can override certain methods and functionality to better fit the requirments of any custom written shaders.
/// An instance of the 'Substance' class can be attached to a 'Mesh-Renderer' where the shader can be 'loaded', 'binded' and excuted during runtime.
/// </summary>
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
	/// <summary>This is where the files for any shaders you want to use should be loaded.</summary>
	virtual bool Load(const std::string location) = 0;
	/// <summary>Any process that needs to occur within the cycle of each frame should be written here.</summary>
	virtual void Update(Transform& transform) = 0;
	/// <summary>Any binding of attributes such as textures should occur here.</summary>
	virtual void Bind() = 0;

	//Virtual methods:
	virtual void Delete();

	//Static methods:
	static GLuint CreateShader(const std::string& source, GLenum type);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string& filename);

};
#endif // !SMART_MATERIAL_H