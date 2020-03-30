#pragma once

#include <glm/fwd.hpp>

#include "Scene.h"

class DefaultScene : public Scene
{
public:
	DefaultScene();

	std::shared_ptr<Entity> CreateCubeEntity(const glm::vec3 &initialPosition);
};

