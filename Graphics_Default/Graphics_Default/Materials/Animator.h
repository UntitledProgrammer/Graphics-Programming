#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

//Includes:
#include<vector>
#include"../Components/Texture.h"

/// <summary>The animator class is designed to be attached to an entity where it will handle the changing of textures during runtime to simulate animation.</summary>
class Animator
{
private:
	//Attributes:
	std::vector<Texture*> frames;

public:
	//Attributes:


	//Constructor:
	Animator();

	//Destructor:
	~Animator();

	//Methods:
};
#endif // !ANIMATOR_H