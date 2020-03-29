#include "CameraComponent.h"

#include <glm/glm.hpp>

CameraComponent::CameraComponent()
{
	fov = glm::radians(75.0f);
	near = 0.1f;
	far = 100.0f;
	active = false;
}

bool CameraComponent::IsActive() const
{
	return active;
}

void CameraComponent::SetActive(bool active)
{
	this->active = active;
}

float CameraComponent::GetFov() const
{
	return fov;
}

void CameraComponent::SetFov(float fov)
{
	this->fov = fov;
}

float CameraComponent::GetNear() const
{
	return near;
}

void CameraComponent::SetNear(float near)
{
	this->near = near;
}

float CameraComponent::GetFar() const
{
	return far;
}

void CameraComponent::SetFar(float far)
{
	this->far = far;
}
