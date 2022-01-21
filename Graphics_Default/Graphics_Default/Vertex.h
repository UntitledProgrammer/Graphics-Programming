#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include<glm.hpp>
#include<vector>

struct Vertex
{
	//Attributes:
	glm::vec3 position;
	/// <summary>Holds the UV coordinates.</summary>
	glm::vec2 uv;

	//Constructor:
	Vertex(glm::vec3 position);
	Vertex(float x, float y, float z);
	Vertex(glm::vec3 pos, glm::vec2 coordinates);

	//Deconstructor:
	~Vertex();
};











struct Primitives
{
	static std::vector<Vertex> Square()
	{
		std::vector<Vertex> verticies;

		verticies.push_back(Vertex(-0.5f, 0.5f, -1.0f));
		verticies.push_back(Vertex(0.5f, 0.5f, -1.0f));
		verticies.push_back(Vertex(0.5, -0.5f, -1.0f));
		verticies.push_back(Vertex(-0.5f, -0.5f, -1.0f));

		return verticies;
	}

	static std::vector<Vertex> Triangle()
	{
		std::vector<Vertex> verticies;

		verticies.push_back(Vertex(0.0f, 0.0f, 0.0f));
		verticies.push_back(Vertex(0.1f, -0.2f, 0.0f));
		verticies.push_back(Vertex(-0.1f, -0.2f, 0.0f));

		return verticies;
	}
};
#endif // !VERTEX_H