#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include<glew.h>
#include<glm.hpp>
#include<SDL_opengl.h>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<vector>
#include"Camera.h"

class Light : public Simulated
{
private:
	//Attributes:
	static Light* defaultInstance;

public:
	//Attributes:
	glm::vec3 colour;
	static std::vector<Light*> lights;

	//Constructor:
	Light();

	//Deconstructor:
	~Light();

	//Methods:
	void draw();
	void Update();
	Simulated* Instantiate()
	{
		Light* light = new Light();
		light->colour = this->colour;
		light->transform = transform;
		return light;
	}

	//Static methods:
	static Light* Instance();
};
#endif // !LIGHT_H