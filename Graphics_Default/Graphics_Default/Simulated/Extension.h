#pragma once
//Includes:
#include"../Management/AdvancedInput.h"

#ifndef EXTENTION_H
#define EXTENTION_H
class Simulated;

/// <summary>Extention is an abstract class that can be used to add extendable function to simulated objects.</summary>
class Extension
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