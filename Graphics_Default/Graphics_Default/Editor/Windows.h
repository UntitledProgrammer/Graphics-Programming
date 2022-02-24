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

#include"Hierarchy.h"
struct Inspector : public Window
{
private:


public:
	//Constructor:
	Inspector()
	{
		name = "Inspector";
	}

	//Methods:
	void Render()
	{
		if (!Hierarchy::selected) return;
		Hierarchy::selected->DrawCentre(50);

		ImGui::Begin("Inspector");

		ImGui::PushItemWidth(90);
		ImGui::SliderFloat("X", &Hierarchy::selected->transform.position.x, 0, 100);
		ImGui::SameLine();
		ImGui::SliderFloat("Y", &Hierarchy::selected->transform.position.y, 0, 100);
		ImGui::SameLine();
		ImGui::SliderFloat("Z", &Hierarchy::selected->transform.position.z, 0, 100);
		ImGui::End();
	}
};








#endif // !WINDOWS_H