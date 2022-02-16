#pragma once
#include"../Shaders/SmartMaterial.h"
class SurfaceMaterial : public Substance
{
private:
	//Attributes:
	enum UniformNames { MODEL_U, PROJECTION_U, VIEW_U, FRAG_LIGHTCOLOUR, FRAG_LIGHTPOS, FRAG_CAMERAPOS, FORWARD, NUM_UNIFORMS };
	GLuint uniforms[NUM_UNIFORMS];

public:
	//Attributes:

	/// <summary>The standard full colour texture as it is intended to look.</summary>
	Texture* base;
	/// <summary>The normal map intended for use with the base texture.</summary>
	Texture* normal;

	//Constructor:
	SurfaceMaterial();

	//Destructor:
	~SurfaceMaterial();

	//Base methods:
	/// <summary>This is where the files for any shaders you want to use should be loaded.</summary>
	bool Load(const std::string location);
	/// <summary>Any process that needs to occur within the cycle of each frame should be written here.</summary>
	void Update(Transform& transform);
	/// <summary>Any binding of attributes such as textures should occur here.</summary>
	void Bind();
};