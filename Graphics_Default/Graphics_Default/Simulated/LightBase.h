#pragma once
#ifndef LIGHT_H
//Defines:
#define LIGHT_H
#define LightSingleton Light::Instance()
#define MAX_LIGHTS 3

//Includes:
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
	Spotlight,
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
	const float nearPlane = 1.0f, farPlane = 100.0f;

	//Constructor:
	Light();
	Light(std::string name, LightCategory category, glm::vec3 colour = glm::vec3(1,1,1));

	//Deconstructor:
	~Light();

	//Methods:
	void Draw();
	void Update();
	glm::mat4 GetProjectionMatrix();
	void OnGui() override
	{
		ImGui::Text("Colour");
		ImGui::PushID("Colour");
		ImGui::SliderFloat("X", &direction.x, -1.0f, 1.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("Y", &direction.y, -1.0f, 1.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("Z", &direction.z, -1.0f, 1.0f);
		ImGui::PopID();

		if (category == LightCategory::Directional || category == LightCategory::Spotlight)
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