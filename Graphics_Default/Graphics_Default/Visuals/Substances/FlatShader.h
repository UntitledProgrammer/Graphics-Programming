#pragma once
#include"../Visuals/Substances/SmartMaterial.h"
class FlatSubstance : public Substance
{
public:
	//Attributes:
	glm::vec3 colour;

	//Constructor:
	FlatSubstance();

	//Destructor:
	~FlatSubstance();

	//Base methods:
	/// <summary>This is where the files for any shaders you want to use should be loaded.</summary>
	bool Load(const std::string location);
	/// <summary>Any process that needs to occur within the cycle of each frame should be written here.</summary>
	void Update(Transform& transform);
	/// <summary>Any binding of attributes such as textures should occur here.</summary>
	void Bind();
};