#pragma once

#include "Scene.h"

class DefaultScene : public Scene
{
public:
	DefaultScene();

	std::shared_ptr<Entity> CreateCubeEntity();
};

