#pragma once
#ifndef SHADER_H
#define SHADER_H
#include<iostream>
#include<glew.h>
#include<string>
#include<fstream>
#include"../Math/Transform.h"
#include"../Simulated/Camera.h"
#include"../Simulated/LightBase.h"
#include"../Components/Texture.h"

class Shader
{
public:
	//Enum:
	enum Types{VERTEX, FRAGMENT, NUM_SHADER_TYPES};
	enum UniformNames{MODEL_U, PROJECTION_U, VIEW_U, FRAG_LIGHTCOLOUR, FRAG_LIGHTPOS, FRAG_CAMERAPOS, FORWARD, NUM_UNIFORMS };

private:
	//Attributes:
	std::string name;
	GLuint program;
	GLuint shaders[NUM_SHADER_TYPES];
	GLuint uniforms[NUM_UNIFORMS];

public:
	//Constructor:
	Shader(const std::string location);

	//Deconstructor:
	~Shader();

	//Methods:
	void update(Transform& transform);
	void litUpdate(Transform& transform, Light& light);
	void Bind(Texture* base, Texture* normal);
	GLuint& getProgram() { return program; }

	//Static methods:
	static GLuint CreateShader(const std::string& source, GLenum type);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string& filename);
};
#endif //SHADER_H
