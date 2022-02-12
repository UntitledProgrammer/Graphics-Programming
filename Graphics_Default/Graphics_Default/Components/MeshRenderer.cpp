#include "MeshRenderer.h"
MeshRenderer::MeshRenderer()
{
	transform = new Transform();
}

MeshRenderer::~MeshRenderer()
{

}

bool MeshRenderer::LoadMesh(std::string location)
{
	return false;
}

bool MeshRenderer::LoadMaterial(std::string location)
{
	return false;
}

void MeshRenderer::ApplyMaterial(Material* material) { this->material = material; }
void MeshRenderer::ApplyMesh(Mesh* mesh) { this->mesh = mesh; }

void MeshRenderer::Render()
{
	material->shader->Bind(material->base, material->normal);
	material->shader->litUpdate(*transform, *Light::Instance());
	mesh->draw();
}