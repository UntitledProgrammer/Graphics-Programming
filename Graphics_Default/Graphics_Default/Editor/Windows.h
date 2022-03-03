#pragma once
#ifndef DEFAULT_WINDOWS_H

//Defines:
#define DEFAULT_WINDOWS_H

//Includes:
#include"Toolbar.h"
#include"../Simulated/Camera.h"

//Context:
//This file stores all the basic default windows that provide basic GUI functonality during the runtime of the project.

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
	//Attributes:
	float pivotScale = 5.0f;

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

		//Window Start:
		ImGui::Begin("Inspector");

		//Draw default GUI attributes:
		ImGui::Text("Default Attributes:");
		ImGui::SliderFloat("Pivot Scale", &pivotScale, 1.0f, 25.0f);
		NewLine(2);
		ImGui::PushItemWidth(90);
		Vec3Slider(&Hierarchy::selected->transform.position,"Position");
		Vec3Slider(&Hierarchy::selected->transform.rotation, "Rotation");
		Vec3Slider(&Hierarchy::selected->transform.scale, "Scale   ");

		//Draw simulated's GUI attributes.
		ImGui::PushID(Hierarchy::selected->GetName().c_str());
		NewLine(4);
		ImGui::Text("Unique Attributes:");
		Hierarchy::selected->OnGui();
		ImGui::PopID();

		ImGui::End();
		//Window end.

		//Draw the lines that indicate where the pivot of a mesh is at in world space.
		Hierarchy::selected->DrawPivot(pivotScale);
	}

private:
	void Vec3Slider(glm::vec3* vector, const char* ID)
	{
		ImGui::PushID(ID);
		ImGui::Text(ID);
		ImGui::SameLine();
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
		ImGui::Text(
			"Welcome!\n"
			"Presented before you is a small demonstration, visualising each technique covered in the 'programming for graphics module'.\n\n"
			"Simulation Information:\n"
			"Information on the simulated enviornment and input/control system can be found on the 'ReadMe' file, available in the main project directory.\n\n"
			"Documentation\n"
			"For the full rundown of each file implemented into this project, please read the 'documentation' file, available in the main project directory.\n\n"
			"Enjoy! T."
		);
		ImGui::End();
	}
};
#endif // !DEFAULT_WINDOWS_H