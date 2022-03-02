#include "Vertex.h"

Vertex::Vertex(glm::vec3 position) : position(position), uv(glm::vec2(0, 0)), tangent(glm::vec3(0)), biTangent(glm::vec3(0)), normal(glm::vec3(0))
{
	tangent = glm::vec3(0);
	biTangent = glm::vec3(0);
}

Vertex::Vertex(float x, float y, float z) : position(glm::vec3(x, y, z)), uv(glm::vec2(0,0)), tangent(glm::vec3(0)), biTangent(glm::vec3(0)), normal(glm::vec3(0))
{
	tangent = glm::vec3(0);
	biTangent = glm::vec3(0);
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 coordinates) : position(pos), uv(coordinates), tangent(glm::vec3(0)), biTangent(glm::vec3(0)), normal(glm::vec3(0))
{
	tangent = glm::vec3(0);
	biTangent = glm::vec3(0);
}

Vertex::Vertex(const Vertex& vertex)
{
	this->position = vertex.position;
	uv = vertex.uv;
	tangent = vertex.tangent;
	biTangent = vertex.biTangent;
	normal = vertex.normal;
}

Vertex::~Vertex()
{

}