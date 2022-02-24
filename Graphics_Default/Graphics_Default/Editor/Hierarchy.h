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
		for (int i =0; i < Simulatables.Size(); i++)
		{
			if (ImGui::TreeNode(std::to_string(i).c_str()))
			{
				if (ImGui::Button("Duplicate"))
				{
					Simulatables.Add(Simulatables.At(i)->Instantiate());
				}
				ImGui::SameLine();
				if (ImGui::Button("Select"))
				{
					selected = Simulatables.At(i);
				}
				ImGui::TreePop();
			}
		}
		if(selected) ImGui::Text(typeid(*selected).name());
		ImGui::End();
	}

	static Simulated* selected;
};
Simulated* Hierarchy::selected = 0;
#endif // !HIERARCHY_H