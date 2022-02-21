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

	//UPDATED
	//Constructors:
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	Mesh(std::vector<Vertex> vertices);

	//Attributes:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; //Unsigned since an indexing number should not be negative.
	unsigned int VAO, VBO, EBO;

	//Methods:
	void DrawUpdated();
	//!UPDATED

public: 
	//Attributes:
	Transform transform;

	//Constructor:
	Mesh(Vertex* verticies, unsigned int verticiesCount, unsigned int* indicies, int indiciesCount);
	Mesh(std::vector<float> verticies);

	//Deconstructor:
	~Mesh();
	
	//Methods:
	void Draw();
	void calculateTangents(Vertex* verticies, unsigned int vertCount, unsigned int* indicies, unsigned int numIndicies);
};
#endif // !MESH_H