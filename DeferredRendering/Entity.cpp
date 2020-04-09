#include "Entity.h"
#include "Component.h"

void Entity::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component.second->Update(this, deltaTime);
	}
}

void Entity::SetInputManager(std::weak_ptr<InputManager> inputManager)
{
	this->inputManager = inputManager;
}

std::weak_ptr<InputManager> Entity::GetInputManager() const
{
	return inputManager;
}
