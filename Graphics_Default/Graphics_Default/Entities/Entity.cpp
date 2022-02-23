#include "Entity.h"

Entity::Entity()
{
	meshRenderer = new MeshRenderer();
	transform = Transform();
	meshRenderer->transform = &transform;
}

Entity::~Entity()
{

}

void Entity::Update()
{
	UpdateExtensions();
	meshRenderer->Render();
}

void Entity::Dismantle()
{
	meshRenderer = nullptr;
	delete this;
}

void Entity::SetMesh(Mesh* mesh)
{
	meshRenderer->ApplyMesh(mesh);
}

void Entity::SetMaterial(Substance* material)
{
	meshRenderer->ApplyMaterial(material);
}
