#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

//Includes:
#include<vector>
#include<SDL.h>
#include"../Components/Texture.h"
#include"Extension.h"
#include"../Visuals/Substances/SurfaceMaterial.h"
#include"../Simulated/Entity.h"

/// <summary>The animator class is designed to be attached to an entity where it will handle the changing of textures during runtime to simulate animation.</summary>
class Animator : public Extension
{
private:
	//Attributes:
	std::vector<Texture*> frames;
	SurfaceMaterial* material;
	float lastframeTime;
	const int startframe = 0;
	unsigned int currentframe;

public:
	//Attributes:
	/// <summary>The delay between each frame before the next texture/frame is introduced. (In miliseconds).</summary>
	float delay = 500.0f;
	bool paused = false;

	//Constructor:
	Animator();

	//Destructor:
	~Animator();

	//Methods:
	void Insert(unsigned int index, Texture* texture);
	void PushBack(Texture* texture);
	void PushFront(Texture* texture);
	
	//Inherited methods:
	void Update();
	void Initialise();
};
#endif // !ANIMATOR_H