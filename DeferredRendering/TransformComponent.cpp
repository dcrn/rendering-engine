#include "TransformComponent.h"

TransformComponent::TransformComponent() :
	position(0.0f),
	orientation(1.0f, 0.0f, 0.0f, 0.0f),
	scale(1.0f)
{
}

glm::vec3 TransformComponent::GetPosition() const
{
	return position;
}

void TransformComponent::SetPosition(glm::vec3 position)
{
	this->position = position;
}

glm::quat TransformComponent::GetOrientation() const
{
	return orientation;
}

void TransformComponent::SetOrientation(glm::quat orientation)
{
	this->orientation = orientation;
}

glm::vec3 TransformComponent::GetScale() const
{
	return scale;
}

void TransformComponent::SetScale(glm::vec3 scale)
{
	this->scale = scale;
}
