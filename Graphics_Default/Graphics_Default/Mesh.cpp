#include "Mesh.h"

Mesh::Mesh(Vertex* verticies, unsigned int verticiesCount, unsigned int* indicies, int indiciesCount)
{
	NumVerts = indiciesCount;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> coordinates;

	for (unsigned int i = 0; i < verticiesCount; i++)
	{
		positions.push_back(verticies[i].position);
		coordinates.push_back(verticies[i].uv);
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

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &verticies);
}

void Mesh::draw()
{
	glBindVertexArray(verticies);
	glDrawElements(GL_TRIANGLES, NumVerts, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
