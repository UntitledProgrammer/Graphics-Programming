#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include<glew.h>
#include<glm.hpp>
#include<SDL_opengl.h>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include"Camera.h"

class Light
{
public:
	//Attributes:
	Transform transform;

	//Constructor:
	Light();

	//Deconstructor:
	~Light();

	//Methods:
	void draw(Camera* camera);
};
#endif // !LIGHT_H