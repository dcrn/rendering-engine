#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/vec3.hpp>

#include "Component.h"

class TransformComponent : Component
{
public:
	constexpr static const char * TYPE = "TransformComponent";

	TransformComponent();

	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 position);
	
	glm::quat GetRotation() const;
	void SetRotation(glm::quat rotation);
	
	glm::vec3 GetScale() const;
	void SetScale(glm::vec3 scale);
	
private:
	glm::vec3 position{};
	glm::quat rotation{};
	glm::vec3 scale{};
};
