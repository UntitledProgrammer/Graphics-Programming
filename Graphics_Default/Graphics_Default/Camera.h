#pragma once
#include "Transform.h"
class Camera
{
public:
	//Attributes:
	Transform transform;
	glm::mat4 projection;

	//Methods:
	glm::vec3 forward();
	glm::vec3 up();
	glm::vec3 right();
	glm::mat4 matrix();

	//Constructor:
	Camera();
	~Camera();
};

