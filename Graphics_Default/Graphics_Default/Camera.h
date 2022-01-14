#pragma once
#include "Transform.h"

//Referenced from: https://brightspace.uos.ac.uk/d2l/le/content/43985/viewContent/598599/View.

class Camera
{
public:
	//Attributes:
	Transform transform;
	glm::mat4 perspective;
	glm::mat4 view;

	//View attributes:
	glm::vec3 forward, up, right;

	//Methods:
	glm::mat4 matrix();
	void Recalculate();

	//Constructor:
	Camera();
	~Camera();
};

