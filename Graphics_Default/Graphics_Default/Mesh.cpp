#include "Mesh.h"

Mesh::Mesh(const float* verts, unsigned int count) : transform(Transform())
{
	/*
	glGenVertexArrays(1, &verticies);
	glBindVertexArray(verticies);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);
	*/
}

Mesh::Mesh(Vertex* verticies, unsigned int verticiesCount, unsigned int* indicies, int indiciesCount)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> coordinates;

	for (unsigned int i = 0; i < verticiesCount; i++)
	{
		positions.push_back(verticies[i].position);
		coordinates.push_back(verticies[i].uv);
	}

	glGenVertexArrays(1, &this->verticies);
	glBindVertexArray(this->verticies);
	glGenBuffers(NUM_BUFFERS, vertexBuffer);

	//Position:
	glEnableVertexAttribArray(POSITION_VB);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_VB, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);

	//Texture Coordinates:
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[TEXTCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(coordinates[0]), &coordinates[0], GL_STATIC_DRAW);
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
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
