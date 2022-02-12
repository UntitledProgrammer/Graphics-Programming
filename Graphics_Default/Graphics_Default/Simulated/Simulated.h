#pragma once
#ifndef SIMULATED_H
#define SIMULATED_H

//Includes:
#include<map>
#include<vector>
#include"../Math/Transform.h"

class Simulated
{
public:
	//Lazy attribute (Branch out into a resource manager or simulated engine class.
	static std::vector<Simulated*> simulatedBodies;

	//Attributes:
	/// <summary>All simulated bodies require a transform component.</summary>
	Transform transform;

	//Abstract methods:
	/// <summary>Update is called during every frame of runtime.</summary>
	virtual void Update() = 0;
};
#endif SIMULATED_H //!SIMULATED_H