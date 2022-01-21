#pragma once
#ifndef SHADER_H
#define SHADER_H
#include<iostream>
#include<glew.h>
#include<string>
#include<fstream>
#include"Transform.h"
#include"Camera.h"

class Shader
{
public:
	//Enum:
	enum Types{VERTEX, FRAGMENT, NUM_SHADER_TYPES};
	enum UniformNames{MODEL_U, PROJECTION_U, VIEW_U, NUM_UNIFORMS };

private:
	//Attributes:
	std::string name;
	GLuint program;
	Camera* camera;
	GLuint shaders[NUM_SHADER_TYPES];
	GLuint uniforms[NUM_UNIFORMS];

public:
	//Constructor:
	Shader(const std::string location, Camera& camera);

	//Deconstructor:
	~Shader();

	//Methods:
	void update(Transform& transform);
	void bind();

	//Static methods:
	static GLuint CreateShader(const std::string& source, GLenum type);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static std::string LoadShader(const std::string& filename);
};
#endif //SHADER_H
