#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include<glew.h>
#include<glm.hpp>
#include<SDL_opengl.h>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include"Camera.h"

class Light : public Simulated
{
public:
	//Attributes:
	glm::vec3 colour;

	//Constructor:
	Light();

	//Deconstructor:
	~Light();

	//Methods:
	void draw();
	void Update();
};
#endif // !LIGHT_H