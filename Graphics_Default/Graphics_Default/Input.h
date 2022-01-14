#pragma once
#include<SDL.h>
#include<iostream>
class Input
{
public:
	//Attributes:
	SDL_Event* sdlEvent = nullptr;

	//Constructor:
	Input();

	//Deconstructor:
	~Input();

	//Methods:
	void update();
	static bool GetKey(SDL_Keycode key);
};

