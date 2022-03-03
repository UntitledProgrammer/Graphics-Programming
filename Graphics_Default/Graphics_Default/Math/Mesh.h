#pragma once
#ifndef MESH_H
#define MESH_H

//Includes:
#include<glm.hpp>
#include<gtx/transform.hpp>
#include<glew.h>
#include<gtx/normal.hpp>
#include"../Math/Transform.h"
#include"../Math/Vertex.h"

/// <summary>A mesh can be thought of as being the skeleton that holds the structure of an object. A mesh is responsable for holding reference to each vertex that 
//forms an object, also providing data about it's indices, normals and tangents that can be passed onto a shader.</summary>
class Mesh
{
private:
	//Enum:
	enum VertexBuffer { POSITION_VB, TEXTCOORD_VB, NORMAL_VB, TANGENT_VB, BITANGENT_VB, INDEX_VB, NUM_BUFFERS };

	//Attributes:
	GLuint vertexBuffer[NUM_BUFFERS];
	/// <summary>Keep's a reference to an array of vertices.</summary>
	GLuint vertexArrayID = 0;
	GLuint NumVerts =0 ;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> normals;

public: 
	//Attributes:
	Transform transform;

	//Constructors:
	/// <summary>The reccomended method for constructing a mesh.</summary>
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool calculateNormals = false);
	/// <summary>In the uncommon situaton where you don't have an indices use this method to construct a mesh that will simply use every vertex supplied.</summary>
	Mesh(std::vector<Vertex> vertices, bool calculateNormals = false);

	//Deconstructor:
	~Mesh();
	
	//Methods:
	void Draw();
	void CalculateTangents(Vertex* vertexArrayID, unsigned int vertCount, unsigned int* indicies, unsigned int numIndicies);
	void Reload(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	void CalculateNormals();
	
	//Friends:
	friend class ResourceManager;
};
#endif // !MESH_H