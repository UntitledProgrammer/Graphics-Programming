#pragma once
#include"../Visuals/Substances/SmartMaterial.h"
class DepthSubstance : public Substance
{
public:
	/// <summary>The standard full colour texture as it is intended to look.</summary>
	Texture* base;
	/// <summary>The normal map intended for use with the base texture.</summary>
	Texture* normal;

	//Attributes:
	glm::vec3 colour;
	glm::mat4 lightSpaceMatrix;

	//Constructor:
	DepthSubstance();

	//Destructor:
	~DepthSubstance();

	//Base methods:
	/// <summary>This is where the files for any shaders you want to use should be loaded.</summary>
	bool Load(const std::string location);
	/// <summary>Any process that needs to occur within the cycle of each frame should be written here.</summary>
	void Update(Transform& transform);
	/// <summary>Any binding of attributes such as textures should occur here.</summary>
	void Bind();
};