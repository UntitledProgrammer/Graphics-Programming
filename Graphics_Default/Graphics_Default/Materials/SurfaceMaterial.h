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
	Texture* base;
	Texture* normal;

	//Constructor:
	SurfaceMaterial();

	//Destructor:
	~SurfaceMaterial();

	//Base methods:
	bool Load(const std::string location);
	void Update(Transform& transform, Light& light);
	void Bind();
};