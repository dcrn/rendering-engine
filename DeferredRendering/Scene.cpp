#include "Scene.h"

#include "Entity.h"
#include "CameraComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"

Scene::Scene() {
	lastFrameTime = std::chrono::high_resolution_clock::now();
}


void Scene::SetInputManager(std::weak_ptr<InputManager> inputManager)
{
	this->inputManager = inputManager;
	for (std::shared_ptr<Entity>& entity : entities)
	{
		entity->SetInputManager(inputManager);
	}
}

void Scene::AddEntity(std::shared_ptr<Entity> entity)
{
	entity->SetInputManager(inputManager);
	entities.push_back(entity);
}

void Scene::Update()
{
	const auto currentFrameTime = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> frameDeltaSeconds = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
	const float deltaTime = frameDeltaSeconds.count();

	activeCameraEntity = std::weak_ptr<Entity>();
	for (std::shared_ptr<Entity>& entity : entities)
	{
		entity->Update(deltaTime);

		if (const auto camera = entity->GetComponent<CameraComponent>())
		{
			if (camera->IsActive())
			{
				activeCameraEntity = entity;
			}
		}
	}
}

void Scene::Render(Renderer* renderer)
{
	if (auto cameraEntity = activeCameraEntity.lock()) {
		if (auto transform = cameraEntity->GetComponent<TransformComponent>())
		{
			renderer->SetView(transform->GetPosition(), transform->GetOrientation());
		}

		if (auto camera = cameraEntity->GetComponent<CameraComponent>())
		{
			renderer->SetProjection(camera->GetFov(), camera->GetNear(), camera->GetFar());
		}
	}

	for (const std::shared_ptr<Entity> &entity : entities)
	{
		renderer->DrawEntity(entity);
	}
}
