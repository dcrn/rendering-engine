#pragma once

#include <chrono>
#include <memory>
#include <vector>

class Entity;

class Scene
{
public:
	Scene();
	void AddEntity(std::shared_ptr<Entity> entity);
	
	void Update();
	void Render();

private:
	std::chrono::high_resolution_clock::time_point lastFrameTime;
	std::vector<std::shared_ptr<Entity>> entities;
	std::shared_ptr<Entity> activeCameraEntity;
};

