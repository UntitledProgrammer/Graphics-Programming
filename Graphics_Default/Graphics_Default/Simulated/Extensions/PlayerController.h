#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

//Includes:
#include"../Simulated.h"
#include"Extension.h"
#include"../Camera.h"

/// <summary>A first person controller is an extention that can be applied to a simulated object to affect it's position and rotation in a simulated world.</summary>
class CameraController : public Extension
{
private:
	//Attributes:
	const SDL_Keycode forward = SDLK_w, backward = SDLK_s, left = SDLK_a, right = SDLK_d, toggle = SDLK_LSHIFT, up = SDLK_q, down = SDLK_e;
	const float speed = 0.2f, sensitivity = 0.1f;
	Camera* camera;
	bool frozen = false;
	float yaw = 0.0f, pitch = 0.0f;
public:
	//Methods:
	virtual void Update()
	{
		if (INPUT->keyPressed(toggle)) { frozen = !frozen; std::cout << "Frozen" << std::endl; }
		if (frozen) { return; }

		//Keyboard movement:
		camera->transform.position += INPUT->getAxis(forward, backward) * speed * camera->forward;
		camera->transform.position += INPUT->getAxis(left, right) * speed * glm::normalize(glm::cross(camera->forward, camera->up));
		camera->transform.position += INPUT->getAxis(down, up) * speed * camera->up;

		//Mouse rotation:
		yaw += -INPUT->MouseDelta().x * sensitivity;
		pitch += INPUT->MouseDelta().y * sensitivity;

		glm::vec3 direction = glm::vec3(glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)), glm::sin(glm::radians(pitch)), glm::sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
		camera->forward = glm::normalize(direction);

		//Adjust position according to any input.
		//body->transform.position += glm::vec3(INPUT->getAxis(right, left) * speed, INPUT->getAxis(down, up) * speed, INPUT->getAxis(forward, backward) * speed);

		//Adjust rotation according to mouse position.
		//body->transform.rotation += glm::vec3(0, INPUT->MouseDelta().x * -sensitivity, INPUT->MouseDelta().y * -sensitivity);
	}

	virtual void Initialise()
	{
		camera = static_cast<Camera*>(body);
	}
};
#endif // CONTROLLER_H