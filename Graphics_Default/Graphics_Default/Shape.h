#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include"Shader.h"
#include"Texture.h"
#include"Mesh.h"
#include"Camera.h"



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
	Texture* texture;
	Camera* camera;

	//Constructor:
	Shape(Camera* camera);

	//Deconstructor:
	~Shape();

	//Methods:
	void draw();
	void setPrimitive(Primitives& verticies);
};
#endif // !SHAPE_H