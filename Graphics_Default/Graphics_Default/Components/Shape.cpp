#include "Shape.h"

Shape::Shape(Camera* camera) : camera(camera)
{
	shader = new Shader("Shaders/LitShader");
	unsigned int indicies[]{ 0,1,2,0,2,3 };
	mesh = new Mesh(&Primitives::Square()[0], Primitives::Square().size(), &indicies[0], 6);
	texture = new Texture();
	normalTexture = new Texture();
	normalTexture->Load("brickwall_normal.jpg");
	texture->Load("brickwall.jpg");
}

Shape::~Shape()
{

}

void Shape::draw(Light& light)
{
	texture->Update();
	shader->litUpdate(mesh->transform, light); //Mesh Renderer.
	mesh->Draw(); //Mesh renderer.
}
