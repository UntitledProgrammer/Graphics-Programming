#include "Vertex.h"

Vertex::Vertex(glm::vec3 position) : position(position), uv(glm::vec2(0, 0))
{

}

Vertex::Vertex(float x, float y, float z) : position(glm::vec3(x, y, z)), uv(glm::vec2(0,0))
{

}

Vertex::Vertex(glm::vec3 pos, glm::vec2 coordinates) : position(pos), uv(coordinates)
{

}

Vertex::~Vertex()
{

}