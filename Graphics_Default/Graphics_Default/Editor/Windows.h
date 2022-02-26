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
		Vec3Slider(&Hierarchy::selected->transform.position,"position");
		ImGui::PushID(Hierarchy::selected->GetName().c_str());
		Hierarchy::selected->OnGui();
		ImGui::PopID();
		ImGui::End();
	}

private:
	void Vec3Slider(glm::vec3* vector, const char* ID)
	{
		ImGui::PushID(ID);
		ImGui::SliderFloat("X", &vector->x, 0, 100);
		ImGui::SameLine();
		ImGui::SliderFloat("Y", &vector->y, 0, 100);
		ImGui::SameLine();
		ImGui::SliderFloat("Z", &vector->z, 0, 100);
		ImGui::PopID();
	}
};








#endif // !WINDOWS_H