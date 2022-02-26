#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include<glew.h>
#include<glm.hpp>
#include<SDL_opengl.h>
#include<gtc/type_ptr.hpp>
#include<SDL.h>
#include<vector>
#include"Camera.h"
#include<imgui.h>

/// <summary>A category of light types that can be used to identify what type a light instance is as well as it's properties.</summary>
enum class LightCategory
{
	Phong,
	Directional,
	Point,
	Flat,
	Size
};

/// <summary>This is the base light class that provides the basic attributes and methods for using lights in a simulated environment.</summary>
class Light : public Simulated
{
private:
	//Attributes:
	static Light* defaultInstance;

public:
	//Attributes:
	glm::vec3 colour, direction = glm::vec3(0.0f,1.0f, 0.0f);
	LightCategory category = LightCategory::Phong;
	static std::vector<Light*> lights;

	//Constructor:
	Light();

	//Deconstructor:
	~Light();

	//Methods:
	void Draw();
	void Update();
	void OnGui() override
	{
		if (category == LightCategory::Directional)
		{
			ImGui::Text("Direction");
			ImGui::SliderFloat("X", &direction.x, -1.0f, 1.0f);
			ImGui::SameLine();
			ImGui::SliderFloat("Y", &direction.y, -1.0f, 1.0f);
			ImGui::SameLine();
			ImGui::SliderFloat("Z", &direction.z, -1.0f, 1.0f);
		}
	}
	Simulated* Instantiate()
	{
		Light* light = new Light();
		light->colour = this->colour;
		light->transform = transform;
		return light;
	}

	//Static methods:
	static Light* Instance();
};
#endif // !LIGHT_H