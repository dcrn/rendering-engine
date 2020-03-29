#pragma once

#include "Component.h"

class FlyMovementComponent : Component
{
public:
	constexpr static const char* TYPE = "FlyMovementComponent";

	void Update(Entity* parent, float deltaTime) override;
};

