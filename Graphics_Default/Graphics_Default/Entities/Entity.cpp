#include "Entity.h"

Entity::Entity()
{
	meshRenderer = nullptr;
	transform = Transform();
}

Entity::~Entity()
{

}

void Entity::Update()
{
	meshRenderer->Render();
}

void Entity::Dismantle()
{
	meshRenderer = nullptr;
	delete this;
}