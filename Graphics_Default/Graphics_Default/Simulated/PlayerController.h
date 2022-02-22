#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

//Includes:
#include"Simulated.h"
#include"Extension.h"

/// <summary>A first person controller is an extention that can be applied to a simulated object to affect it's position and rotation in a simulated world.</summary>
class PlayerController : public Extension
{
private:
	//Attributes:
	const SDL_Keycode forward = SDLK_w, backward = SDLK_s, left = SDLK_a, right = SDLK_d, toggle = SDLK_LSHIFT, up = SDLK_q, down = SDLK_e;
	const float speed = 0.2f, sensitivity = 0.1f;
	bool frozen = false;
public:
	//Methods:
	virtual void Update()
	{
		if (INPUT->keyDown(toggle)) { frozen = !frozen; std::cout << "KEY"; }
		if (frozen) { return; }

		//Adjust position according to any input.
		body->transform.position += glm::vec3(INPUT->getAxis(right, left) * speed, INPUT->getAxis(down, up) * speed, INPUT->getAxis(forward, backward) * speed);

		//Adjust rotation according to mouse position.
		body->transform.rotation += glm::vec3(0, INPUT->MouseDelta().x * -sensitivity, INPUT->MouseDelta().y * -sensitivity);
	}

	virtual void Initialise()
	{

	}
};
#endif // CONTROLLER_H