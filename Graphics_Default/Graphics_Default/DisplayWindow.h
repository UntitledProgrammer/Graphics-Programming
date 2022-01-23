#pragma once
#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H
#include<string>
#include<imgui.h>
#include<backends/imgui_impl_sdl.h>
#include<imgui_sdl.h>
#include<imgui_internal.h>
#include<SDL.h>

class DisplayWindow
{
private:
	//Attributes:
	SDL_Window* window;
	SDL_GLContext context;

public:
	//Constructor:
	DisplayWindow(SDL_Window* window);
	//DisplayWindow() : polygon(nullptr), context(nullptr) {};

	//Deconstructor:
	~DisplayWindow();

	//Methods:
	void Update();
};
#endif // !DISPLAY_WINDOW_H
