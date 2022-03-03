#pragma once
#ifndef TOOLBAR_H
#define TOOLBAR_H

//Includes:
#include<vector>
#include<string>
#include<SDL.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include<imgui.h>
#include<backends/imgui_impl_sdl.h>
#include<backends/imgui_impl_opengl3.h>
#include"../Constants.h"

//Base class:

/// <summary>Window is an interface class that provides several attributes needed to add it to the rendering pile during simulation.</summary>
class Window
{
public:
	//Abstract methods:
	/// <summary>Render will be called on during every frame of simulation; write your ImGui draw code here.</summary>
	virtual void Render() = 0;
	void NewLine(int rows){ for (int i = 0; i < rows; i++) { ImGui::Spacing(); } }
	/// <summary>The name / ID this instance of window will be refered to as.</summary>
	std::string name = "Default";
	/// <summary>When true this instance of window will be displayed on screen, when false it will it will be inactive on screen but persist in memory.</summary>
	bool active = false;
};


class Toolbar
{
private:
	//Attributes:
	std::vector<Window*> windows;
	SDL_Window* window;
public:
	//Constructor:
	Toolbar(SDL_Window* window, SDL_GLContext* context);

	//Destructor:
	~Toolbar();

	//Methods:
	void Update();
	/// <summary>Add's default windows to toolbar.</summary>
	void LoadDefault();
};
#endif // !TOOLBAR_H