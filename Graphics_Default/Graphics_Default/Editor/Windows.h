#pragma once
#include"Toolbar.h"
#ifndef WINDOWS_H
#define WINDOWS_H
#include"../Simulated/Camera.h"
struct Menu : public Window
{
private:
	//Attributes:

public:
	//Constructor:
	Menu()
	{
		name = "Menu";
	}

	//Methods:
	void Render()
	{
		ImGui::Begin(name.c_str());

		if (ImGui::Button("Documentation"))
		{

		}


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
		Vec3Slider(&Hierarchy::selected->transform.rotation, "rotation");
		ImGui::PushID(Hierarchy::selected->GetName().c_str());
		Hierarchy::selected->OnGui();
		ImGui::PopID();
		ImGui::End();
	}

private:
	void Vec3Slider(glm::vec3* vector, const char* ID)
	{
		ImGui::PushID(ID);
		ImGui::SliderFloat("X", &vector->x, vector->x - 0.5, vector->x + 0.5);
		ImGui::SameLine();
		ImGui::SliderFloat("Y", &vector->y, vector->y - 0.5, vector->y + 0.5);
		ImGui::SameLine();
		ImGui::SliderFloat("Z", &vector->z, vector->z - 0.5, vector->z + 0.5);
		ImGui::PopID();
	}
};


struct Information : public Window
{
private:


public:
	//Constructor:
	Information()
	{
		name = "Information";
	}

	//Methods:
	void Render()
	{
		ImGui::Begin(name.c_str());
		//ImGui::Text("Camera\n wdw");

		ImGui::End();
	}
};



#endif // !WINDOWS_H