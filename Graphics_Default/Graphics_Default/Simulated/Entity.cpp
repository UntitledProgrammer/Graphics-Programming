#include "Entity.h"

Entity::Entity()
{
	meshRenderer = new MeshRenderer();
	transform = Transform();
	meshRenderer->transform = &transform;
	SetName("Entity");
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

Simulated* Entity::Instantiate()
{
	Entity* entity = new Entity();
	entity->SetMaterial(meshRenderer->material);
	entity->SetMesh(meshRenderer->mesh);
	entity->transform = transform;
	return entity;
}

void Entity::SetMesh(Mesh* mesh)
{
	this->meshRenderer->ApplyMesh(mesh);
}

void Entity::SetMaterial(Substance* material)
{
	meshRenderer->ApplyMaterial(material);
}
