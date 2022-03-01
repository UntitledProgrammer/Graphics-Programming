#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, bool calculateNormals) : vertices(vertices), indices(indices)
{
	if (calculateNormals) CalculateNormals();
	Reload(this->vertices, this->indices);
}

Mesh::Mesh(std::vector<Vertex> vertices, bool calculateNormals) : vertices(vertices), indices(indices)
{
	//Add indices:
	std::vector<unsigned int> indices;
	for (int i = 0; i < vertices.size(); i++) { indices.push_back(i); }

	if (calculateNormals) CalculateNormals();

	//Load mesh.
	Reload(vertices, indices);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertexArrayID);
}

void Mesh::Draw()
{
	glBindVertexArray(vertexArrayID);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::CalculateTangents(Vertex* vertices, unsigned int vertCount, unsigned int* indices, unsigned int numIndicies)
{
	//Calculate tangent and bitangent:
	for (unsigned int i = 0; i < numIndicies; i += 3)
	{
		Vertex v0 = vertices[indices[i]];
		Vertex v1 = vertices[indices[i+1]];
		Vertex v2 = vertices[indices[i+2]];

		glm::vec3 edge1 = v1.position - v0.position;
		glm::vec3 edge2 = v2.position - v0.position;

		GLfloat deltaU1 = v1.uv.x - v0.uv.x;
		GLfloat deltaV1 = v1.uv.y - v0.uv.y;
		GLfloat deltaU2 = v2.uv.x - v0.uv.x;
		GLfloat deltaV2 = v2.uv.y - v0.uv.y;

		GLfloat f = 1.0f / (deltaU1 * deltaV1 - deltaU2 * deltaV1);

		glm::vec3 tangent;
		glm::vec3 bitangent;

		tangent.x = f * (deltaV2 * edge1.x - deltaV1 * edge2.x);
		tangent.y = f * (deltaV2 * edge1.y - deltaV1 * edge2.y);
		tangent.z = f * (deltaV2 * edge1.z - deltaV1 * edge2.y);

		bitangent.x = f * (-deltaU2 * edge1.x + deltaU1 * edge2.x);
		bitangent.y = f * (-deltaU2 * edge1.y + deltaU1 * edge2.y);
		bitangent.z = f * (-deltaU2 * edge1.z + deltaU1 * edge2.z);

		v0.tangent += tangent;
		v1.tangent += tangent;
		v2.tangent += tangent;

		v0.biTangent += bitangent;
		v1.biTangent += bitangent;
		v2.biTangent += bitangent;

		vertices[indices[i]] = v0;
		vertices[indices[i+1]] = v1;
		vertices[indices[i+2]] = v2;
	}

	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertices[i].tangent = glm::normalize(vertices[i].tangent);
		vertices[i].biTangent = glm::normalize(vertices[i].biTangent);
	}

}

void Mesh::Reload(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	NumVerts = indices.size();
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> coordinates;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> biTangents;

	CalculateTangents(vertices.data(), vertices.size(), indices.data(), indices.size());

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		positions.push_back(vertices[i].position);
		coordinates.push_back(vertices[i].uv);
		tangents.push_back(vertices[i].tangent);
		biTangents.push_back(vertices[i].biTangent);
		normals.push_back(vertices[i].normal);
	}


	//Generate vertex arrays:
	glGenVertexArrays(1, &this->vertexArrayID);
	glBindVertexArray(this->vertexArrayID);
	glGenBuffers(NUM_BUFFERS, vertexBuffer);

	//Tangents & Bitangents:
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[TANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(tangents[0]), &tangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TANGENT_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TANGENT_VB);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[BITANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(biTangents[0]), &biTangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(BITANGENT_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(BITANGENT_VB);

	//Normals:
	glEnableVertexAttribArray(NORMAL_VB);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Position:
	glEnableVertexAttribArray(POSITION_VB);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	//Texture Coordinates:
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[TEXTCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(coordinates[0]), &coordinates[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TEXTCOORD_VB);

	//Index:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	
	//Bind array:
	glBindVertexArray(0);
}

void Mesh::CalculateNormals()
{
	normals.clear();
	for (int i = 0; i < indices.size(); i += 3)
	{
		glm::vec3 a = vertices[indices[i]].position;
		glm::vec3 b = vertices[indices[i+1]].position;
		glm::vec3 c = vertices[indices[i+2]].position;

		glm::vec3 normal = glm::triangleNormal(a, b, c);
		vertices[indices[i]].normal = normal;
		vertices[indices[i+1]].normal = normal;
		vertices[indices[i+2]].normal = normal;
	}
}