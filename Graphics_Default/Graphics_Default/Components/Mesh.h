#pragma once
#ifndef MESH_H
#define MESH_H

#include<glm.hpp>
#include<gtx/transform.hpp>
#include<glew.h>
#include<gtx/normal.hpp>
#include"../Math/Transform.h"
#include"../Math/Vertex.h"

class Mesh
{
private:
	//Enum:
	enum VertexBuffer { POSITION_VB, TEXTCOORD_VB, NORMAL_VB, TANGENT_VB, BITANGENT_VB, INDEX_VB, NUM_BUFFERS };

	//Attributes:
	GLuint vertexBuffer[NUM_BUFFERS];
	/// <summary>Keep's a reference to an array of vertices.</summary>
	GLuint verticies = 0;
	GLuint NumVerts =0 ;

public: 
	//Attributes:
	Transform transform;

	//Constructor:
	Mesh(Vertex* verticies, unsigned int verticiesCount, unsigned int* indicies, int indiciesCount);

	//Deconstructor:
	~Mesh();
	
	//Methods:
	void draw();
	void calculateTangents(Vertex* verticies, unsigned int vertCount, unsigned int* indicies, unsigned int numIndicies);
};
#endif // !MESH_H