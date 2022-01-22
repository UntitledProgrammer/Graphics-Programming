#include "Shape.h"

Shape::Shape(Camera* camera) : camera(camera)
{
	shader = new Shader("Shaders/Basic", *camera);
	unsigned int indicies[]{ 0,1,2,0,2,3 };
	mesh = new Mesh(&Primitives::Square()[0], Primitives::Square().size(), &indicies[0], 6);
	texture = new Texture();
	texture->load("brickwall.jpg");
}

Shape::~Shape()
{

}

void Shape::draw()
{
	texture->update();
	shader->update(mesh->transform);
	mesh->draw();
}
