#pragma once
#include<glm.hpp>
#include<gtx/transform.hpp>
#include<glew.h>
#include"Transform.h"
#include"Vertex.h"

class Mesh
{
private:

	//Attributes:
	GLuint vertexBuffer[2];
	/// <summary>Keep's a reference to an array of vertices.</summary>
	GLuint verticies = 0;

public: 
	//Attributes:
	Transform transform;

	//Constructor:
	Mesh(const float* verts, unsigned int count);
	Mesh(Vertex* verticies, unsigned int verticiesCount, unsigned int* indicies, int indiciesCount);

	//Deconstructor:
	~Mesh();

	//Methods:
	void draw();
};

