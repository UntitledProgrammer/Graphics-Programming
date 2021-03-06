#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include"../Visuals/Shader.h"
#include"../Visuals/Textures/Texture.h"
#include"../Math/Mesh.h"
#include"../Simulated/Camera.h"



/// <summary>
/// The idea of the shape class is to bind a texture, shader and mesh all into one object.
/// 
/// 
/// 
/// </summary>
class Shape
{
public:
	//Attributes:
	Mesh* mesh;
	Shader* shader;
	Texture* texture, *normalTexture;
	Camera* camera;

	//Constructor:
	Shape(Camera* camera);

	//Deconstructor:
	~Shape();

	//Methods:
	void draw(Light& light);
	void setPrimitive(Primitives& vertexArrayID);
};
#endif // !SHAPE_H