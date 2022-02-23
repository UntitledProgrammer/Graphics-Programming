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
	/// <summary>The reccomended method for constructing a mesh.</summary>
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	/// <summary>In the uncommon situaton where you don't have an indices use this method to construct a mesh that will simply use every vertex supplied.</summary>
	Mesh(std::vector<Vertex> vertices);

	//Deconstructor:
	~Mesh();
	
	//Methods:
	void Draw();
	void calculateTangents(Vertex* verticies, unsigned int vertCount, unsigned int* indicies, unsigned int numIndicies);
	void Reload(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	
	//Friends:
	friend class ResourceManager;
};
#endif // !MESH_H