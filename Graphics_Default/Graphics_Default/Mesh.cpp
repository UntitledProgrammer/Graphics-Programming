#include "Mesh.h"

Mesh::Mesh(const float* verts, unsigned int count) : transform(Transform())
{
	glGenVertexArrays(1, &vertices);
	glBindVertexArray(vertices);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vertices);
}

void Mesh::draw()
{
	glBindVertexArray(vertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
