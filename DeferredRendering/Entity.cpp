#include "Entity.h"
#include "Component.h"

void Entity::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component.second->Update(this, deltaTime);
	}
}
