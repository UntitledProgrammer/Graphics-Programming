#pragma once
#include"Toolbar.h"
#ifndef WINDOWS_H
#define WINDOWS_H
#include"../Simulated/Camera.h"
struct Menu : public Window
{
private:
	//Attributes:
	glm::vec3* position, *rotation;

public:
	//Constructor:
	Menu()
	{
		name = "Menu";
		position = &Camera::Instance()->transform.position;
		rotation = &Camera::Instance()->transform.rotation;
	}

	//Methods:
	void Render()
	{
		ImGui::Begin("Menu");
		ImGui::Text("Main Camera");
		ImGui::Text("Position");


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