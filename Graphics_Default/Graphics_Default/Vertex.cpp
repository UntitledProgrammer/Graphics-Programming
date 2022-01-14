#include "Vertex.h"

Vertex::Vertex(glm::vec3 position) : position(position)
{

}

Vertex::Vertex(float x, float y, float z) : position(glm::vec3(x, y, z))
{

}

Vertex::~Vertex()
{

}