#pragma once
#include<glm.hpp>
#include<gtx/transform.hpp>
#include<glew.h>

class Mesh
{
private:

	//Attributes:
	GLuint vertexBuffer = 0;
	/// <summary>Keep's a reference to an array of vertices.</summary>
	GLuint vertices = 0;

public: 

	//Constructor:
	Mesh(float* verts, unsigned int count);

	//Deconstructor:
	~Mesh();

	//Methods:
	void draw();
};

