#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
	position = glm::zero<glm::vec3>();
	rotation = glm::zero<glm::quat>();
	scale = glm::identity<glm::vec3>();
}

glm::vec3 TransformComponent::GetPosition() const
{
	return position;
}

void TransformComponent::SetPosition(glm::vec3 position)
{
	this->position = position;
}

glm::quat TransformComponent::GetRotation() const
{
	return rotation;
}

void TransformComponent::SetRotation(glm::quat rotation)
{
	this->rotation = rotation;
}

glm::vec3 TransformComponent::GetScale() const
{
	return scale;
}

void TransformComponent::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}
