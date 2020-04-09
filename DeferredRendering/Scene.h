#pragma once

#include <chrono>
#include <memory>
#include <vector>

class Entity;
class Renderer;
class InputManager;

class Scene
{
public:
	Scene();

	void SetInputManager(std::weak_ptr<InputManager> inputManager);
	void AddEntity(std::shared_ptr<Entity> entity);
	
	void Update();
	void Render(Renderer* renderer);

private:
	std::chrono::high_resolution_clock::time_point lastFrameTime;
	std::vector<std::shared_ptr<Entity>> entities;
	std::weak_ptr<Entity> activeCameraEntity;
	std::weak_ptr<InputManager> inputManager;
};

