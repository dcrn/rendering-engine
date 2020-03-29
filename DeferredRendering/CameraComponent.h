#pragma once

#include "Component.h"

class CameraComponent : public Component
{
public:
	constexpr static const char* TYPE = "CameraComponent";

	CameraComponent();

	bool IsActive() const;
	void SetActive(bool active);
	
	float GetFov() const;
	void SetFov(float fov);
	
	float GetNear() const;
	void SetNear(float near);
	
	float GetFar() const;
	void SetFar(float far);
private:
	bool active;	
	float fov;
	float near;
	float far;
};

