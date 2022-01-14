#pragma once
#include<glm.hpp>
#include<gtx/transform.hpp>
#include<glew.h>
#include"Transform.h"

class Mesh
{
private:

	//Attributes:
	GLuint vertexBuffer = 0;
	/// <summary>Keep's a reference to an array of vertices.</summary>
	GLuint vertices = 0;

public: 
	//Attributes:
	Transform transform;

	//Constructor:
	Mesh(const float* verts, unsigned int count);

	//Deconstructor:
	~Mesh();

	//Methods:
	void draw();
};

