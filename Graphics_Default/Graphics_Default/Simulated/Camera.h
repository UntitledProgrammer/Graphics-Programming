#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include"Simulated.h"
#include"../Constants.h"

//Testing:
#include<glew.h>
#include<glm.hpp>
#include<SDL_opengl.h>
#include<gtc/type_ptr.hpp>
#include<SDL.h>

//Referenced from: https://brightspace.uos.ac.uk/d2l/le/content/43985/viewContent/598599/View.
//Referenced from: https://cpp.hotexamples.com/examples/-/glm/perspective/cpp-glm-perspective-method-examples.html.

class Camera : public Simulated
{
public:
	//Attributes:
	glm::mat4 perspective;
	glm::mat4 view;
	float fov = 45.0f;
	float aspect = (float) WINDOW_WIDTH / WINDOW_HEIGHT;
	static Camera* defaultInstance;

	//View attributes:
	glm::vec3 forward, up, right, target;

	//Methods:
	glm::mat4 GetMatrix();
	void recalculate();
	void Update();
	glm::vec3 Direction() { return glm::normalize(transform.position - target); }

	//Static methods:
	static Camera* Instance();

	//Constructor:
	Camera();
	~Camera();
};
#endif // !CAMERA_H