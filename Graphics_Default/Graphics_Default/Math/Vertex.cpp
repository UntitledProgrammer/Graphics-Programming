#include "Vertex.h"

Vertex::Vertex(glm::vec3 position) : position(position), uv(glm::vec2(0, 0))
{
	tangent = glm::vec3(0);
	biTangent = glm::vec3(0);
}

Vertex::Vertex(float x, float y, float z) : position(glm::vec3(x, y, z)), uv(glm::vec2(0,0))
{
	tangent = glm::vec3(0);
	biTangent = glm::vec3(0);
}

Vertex::Vertex(glm::vec3 pos, glm::vec2 coordinates) : position(pos), uv(coordinates)
{
	tangent = glm::vec3(0);
	biTangent = glm::vec3(0);
}

Vertex::~Vertex()
{

}

std::vector<Vertex*> Vertex::ArrayToVertex(float vertz[])
{
	std::vector<Vertex*> verticies;
	for (int i = 0; vertz[i] != NULL; i+=3)
	{
		if (vertz[i] == NULL) return verticies;
		verticies.push_back(new Vertex(glm::vec3(vertz[i], vertz[i + 1], vertz[i + 2])));
	}
	return verticies;
}
