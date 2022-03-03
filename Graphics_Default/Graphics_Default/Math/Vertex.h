#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include<glm.hpp>
#include<vector>

/// <summary>Mathematically, a vertex is where two or more lines, curves or edges meet. This structure in practice is much the same with the addition
///that it not only denotes the position of two or more lines meeting but also the normal, tangent and bi-tangent of the two lines.</summary>
struct Vertex
{
	//Attributes:
	glm::vec3 position, tangent, biTangent, normal;
	/// <summary>Holds the UV coordinates.</summary>
	glm::vec2 uv;

	//Constructor:
	Vertex() : position(glm::vec3(0)), tangent(glm::vec3(0)), biTangent(glm::vec3(0)), uv(glm::vec2(0)), normal(glm::vec3(0)) {};
	Vertex(glm::vec3 position);
	Vertex(float x, float y, float z);
	Vertex(glm::vec3 pos, glm::vec2 coordinates);
	Vertex(const Vertex &vertex);

	//Deconstructor:
	~Vertex();
};






struct Primitives
{
	std::vector<Vertex> vertexArrayID;
	std::vector<unsigned int> indices;

	static std::vector<Vertex> Square()
	{
		std::vector<Vertex> vertices;

		vertices.push_back(Vertex( glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0,0) ));
		vertices.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1, 0)));
		vertices.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1, 1)));
		vertices.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0, 1)));

		return vertices;
	}

	static std::vector<unsigned int> SqaureIndices()
	{
		std::vector<unsigned int> indices = { 0, 1, 2, 0, 2, 3 };
		return indices;
	}

	static std::vector<Vertex> Triangle()
	{
		std::vector<Vertex> vertices;

		vertices.push_back(Vertex(0.0f, 0.0f, 0.0f));
		vertices.push_back(Vertex(0.1f, -0.2f, 0.0f));
		vertices.push_back(Vertex(-0.1f, -0.2f, 0.0f));

		return vertices;
	}
};
#endif // !VERTEX_H