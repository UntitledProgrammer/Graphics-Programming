#pragma once
#include"Toolbar.h"
#ifndef WINDOWS_H
#define WINDOWS_H

struct Menu : public Window
{
public:
	//Constructor:
	Menu()
	{
		name = "Menu";
	}

	//Methods:
	void Render()
	{
		ImGui::Begin("Menu");
		ImGui::End();
	}
};

struct Inspector : public Window
{
public:
	//Constructor:
	Inspector()
	{
		name = "Inspector";
	}

	//Methods:
	void Render()
	{
		ImGui::Begin("Inspector");
		ImGui::End();
	}
};








#endif // !WINDOWS_H