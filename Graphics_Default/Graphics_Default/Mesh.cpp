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

	glGenVertexArrays(1, &this->verticies);
	glBindVertexArray(this->verticies);

	glGenBuffers(2, vertexBuffer);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, verticiesCount * sizeof(Vertex), verticies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Bind indicies:
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesCount * sizeof(unsigned int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);

	//glBindVertexArray(0);

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
