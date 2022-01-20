#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"
#include"Constants.h"

//Referenced from: https://brightspace.uos.ac.uk/d2l/le/content/43985/viewContent/598599/View.
//Referenced from: https://cpp.hotexamples.com/examples/-/glm/perspective/cpp-glm-perspective-method-examples.html.

class Camera
{
public:
	//Attributes:
	Transform transform;
	glm::mat4 perspective;
	glm::mat4 view;
	float fov = 45.0f;
	float aspect = (float) WINDOW_WIDTH / WINDOW_HEIGHT;

	//View attributes:
	glm::vec3 forward, up, right;

	//Methods:
	glm::mat4 matrix();
	void Recalculate();

	//Constructor:
	Camera();
	~Camera();
};
#endif // !CAMERA_H