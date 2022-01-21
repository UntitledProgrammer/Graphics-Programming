#pragma once
#ifndef MESH_H
#define MESH_H

#include<glm.hpp>
#include<gtx/transform.hpp>
#include<glew.h>
#include"Transform.h"
#include"Vertex.h"

class Mesh
{
private:
	//Enum:
	enum VertexBuffer { POSITION_VB, TEXTCOORD_VB, INDEX_VB, NUM_BUFFERS };

	//Attributes:
	GLuint vertexBuffer[NUM_BUFFERS];
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
#endif // !MESH_H