#pragma once
//Includes:
#include"Simulated.h"
#include"../Management/AdvancedInput.h"

#ifndef EXTENTION_H
#define EXTENTION_H

/// <summary>Extention is an abstract class that can be used to add extendable function to simulated objects.</summary>
class Extention
{
public:
	//Attributes:
	/// <summary>Represents the physical body of the object this extention is applied to.</summary>
	Simulated* body = nullptr;

	//Methods:

	/// <summary>Any logic that needs to be updated per frame should be implemented in the scope of the update method.</summary>
	virtual void Update() = 0;
	/// <summary>Any logic that needs to happen once during the start of the program should be processed here.</summary>
	virtual void Initialise() = 0;
}; 
#endif // EXTENTION_H


#ifndef CONTROLLER_H
#define CONTROLLER_H

/// <summary>A first person controller is an extention that can be applied to a simulated object to affect it's position and rotation in a simulated world.</summary>
class PlayerController : public Extention
{
private:
	//Attributes:
	//Depth:
	const SDL_Keycode forward = SDLK_w, backward = SDLK_s;
	//Horizontal:
	const SDL_Keycode left = SDLK_a, right = SDLK_d;
	const float speed = 0.2f, sensitivity = 0.1f;

public:
	//Methods:
	virtual void Update()
	{
		//Adjust position according to any input.
		body->transform.position = glm::vec3(body->transform.position.x += INPUT->getAxis(right, left) * speed, 0, INPUT->getAxis(forward, backward) * speed);

		//Adjust rotation according to mouse position.
		body->transform.rotation += glm::vec3(0, INPUT->MouseDelta().x * -sensitivity, INPUT->MouseDelta().y * -sensitivity);
	}

	virtual void Initialise()
	{

	}
};
#endif // CONTROLLER_H