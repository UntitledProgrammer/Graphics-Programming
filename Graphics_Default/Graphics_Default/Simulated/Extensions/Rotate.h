#pragma once
#ifndef ROTATE_H
#define ROTATE_H

//Includes:
#include"../Simulated.h"
#include"Extension.h"
#include"../../Math/Transform.h"
/// <summary>A first person controller is an extention that can be applied to a simulated object to affect it's position and rotation in a simulated world.</summary>
class Rotate : public Extension
{
private:
	//Attributes:
	const float angularSpeed = 0.01f;
public:
	//Methods:
	virtual void Update()
	{
		body->transform.rotation += angularSpeed;
	}

	virtual void Initialise()
	{

	}
};
#endif //!ROTATE_H