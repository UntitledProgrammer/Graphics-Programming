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
	return material->Load(location);
}

void MeshRenderer::ApplyMaterial(Substance* material) { this->material = material; }
void MeshRenderer::ApplyMesh(Mesh* mesh) { this->mesh = mesh; }

void MeshRenderer::SetTransform(Transform* transform)
{
	this->transform = transform;
}

void MeshRenderer::Render()
{
	material->Bind();
	material->Update(*transform);
	mesh->Draw();
}