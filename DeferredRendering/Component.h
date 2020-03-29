#pragma once

class Entity;

class Component
{
public:
	virtual ~Component() = default;

	virtual void Update(Entity* parent, float deltaTime);
};
