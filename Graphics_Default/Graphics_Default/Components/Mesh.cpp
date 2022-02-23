#include "Mesh.h"

Mesh::Mesh(Vertex* verticies, unsigned int verticiesCount, unsigned int* indicies, int indiciesCount)
{
	NumVerts = indiciesCount;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> coordinates;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> biTangents;

	calculateTangents(verticies, verticiesCount, indicies, indiciesCount);

	for (unsigned int i = 0; i < verticiesCount; i++)
	{
		positions.push_back(verticies[i].position);
		coordinates.push_back(verticies[i].uv);
		tangents.push_back(verticies[i].tangent);
		biTangents.push_back(verticies[i].biTangent);
	}

	//Lighting:
	std::vector<glm::vec3> normals;
	normals.resize(verticiesCount);
	for (int i = 0; i < indiciesCount; i+=3)
	{
		glm::vec3 a = positions[indicies[i]];
		glm::vec3 b = positions[indicies[i+1]];
		glm::vec3 c = positions[indicies[i]+2];

		glm::vec3 normal = glm::triangleNormal(a, b, c);
		normals[indicies[i]] += normal;
		normals[indicies[i+1]] += normal;
		normals[indicies[i+2]] += normal;
	}

	//Tangents & Bitangents:
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[TANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(tangents[0]), &tangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TANGENT_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TANGENT_VB);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[BITANGENT_VB]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(biTangents[0]), &biTangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(BITANGENT_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(BITANGENT_VB);

	//Normals:
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(NORMAL_VB);
	//Lighting:

	glGenVertexArrays(1, &this->verticies);
	glBindVertexArray(this->verticies);
	glGenBuffers(NUM_BUFFERS, vertexBuffer);

	//Position:
	glEnableVertexAttribArray(POSITION_VB);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Texture Coordinates:
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[TEXTCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, indiciesCount * sizeof(coordinates[0]), &coordinates[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEXTCOORD_VB, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(TEXTCOORD_VB);


	//Index:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	Reload(vertices, indices);
}

Mesh::Mesh(std::vector<Vertex> vertices)
{
	//Add indices:
	std::vector<unsigned int> indices;
	for (int i = 0; i < vertices.size(); i++) { indices.push_back(i); }
	//Load mesh.
	Reload(vertices, indices);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &verticies);
}

void Mesh::Draw()
{
	glBindVertexArray(verticies);
	glDrawElements(GL_TRIANGLES, NumVerts, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::calculateTangents(Vertex* verticies, unsigned int vertCount, unsigned int* indicies, unsigned int numIndicies)
{
	//Calculate tangent and bitangent:
	for (unsigned int i = 0; i < numIndicies; i += 3)
	{
		Vertex v0 = verticies[indicies[i]];
		Vertex v1 = verticies[indicies[i+1]];
		Vertex v2 = verticies[indicies[i+2]];

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

		verticies[indicies[i]] = v0;
		verticies[indicies[i+1]] = v1;
		verticies[indicies[i+2]] = v2;
	}

	for (unsigned int i = 0; i < vertCount; i++)
	{
		verticies[i].tangent = glm::normalize(verticies[i].tangent);
		verticies[i].biTangent = glm::normalize(verticies[i].biTangent);
	}

}

void Mesh::Reload(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
	NumVerts = indices.size();
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> coordinates;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> biTangents;

	calculateTangents(vertices.data(), vertices.size(), indices.data(), indices.size());

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		positions.push_back(vertices[i].position);
		coordinates.push_back(vertices[i].uv);
		tangents.push_back(vertices[i].tangent);
		biTangents.push_back(vertices[i].biTangent);
	}

	//Normals:
	std::vector<glm::vec3> normals;
	normals.resize(vertices.size());
	for (int i = 0; i < indices.size(); i += 3)
	{
		glm::vec3 v1 = positions[indices[i]];
		glm::vec3 v2 = positions[indices[i + 1]];
		glm::vec3 v3 = positions[indices[i + 2]];
		glm::vec3 normal = glm::triangleNormal(v1, v2, v3);
		normals[indices[i]] += normal;
		normals[indices[i + 1]] += normal;
		normals[indices[i + 2]] += normal;
	}

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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(NORMAL_VB);

	//Lighting:
	glGenVertexArrays(1, &this->verticies);
	glBindVertexArray(this->verticies);
	glGenBuffers(NUM_BUFFERS, vertexBuffer);

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

	glBindVertexArray(0);
}
