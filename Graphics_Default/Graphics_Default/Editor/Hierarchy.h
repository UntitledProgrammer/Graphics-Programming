#pragma once
#ifndef HIERARCHY_H
#define HIERARCHY_H

//Includes:
#include"Windows.h"
#include"../Management/ResourceManager.h"

class Hierarchy : public Window
{
public:
	//Constructor:
	Hierarchy() { name = "Hierarchy"; }

	//Inherited methods:
	void Render()
	{
		ImGui::Begin(name.c_str());

		//Draw a button for each simulatable:
		for (std::map<std::string, Simulated*>::iterator it = Simulatables.resources.begin(); it != Simulatables.resources.end(); it++)
		{
			if (ImGui::Button(it->first.c_str()))
			{
				selected = it->second;
			}
		}
		if(selected) ImGui::Text(typeid(*selected).name());
		ImGui::End();
	}

	static Simulated* selected;
};
Simulated* Hierarchy::selected = 0;
#endif // !HIERARCHY_H