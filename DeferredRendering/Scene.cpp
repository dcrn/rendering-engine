#include "Scene.h"

#include "Entity.h"
#include "CameraComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"

Scene::Scene()
{
	lastFrameTime = std::chrono::high_resolution_clock::now();
}


void Scene::AddEntity(std::shared_ptr<Entity> entity)
{
	entities.push_back(entity);
}

void Scene::Update()
{
	const auto currentFrameTime = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> frameDeltaSeconds = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
	const float deltaTime = frameDeltaSeconds.count();

	activeCameraEntity = nullptr;
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
	if (activeCameraEntity) {
		if (auto transform = activeCameraEntity->GetComponent<TransformComponent>())
		{
			renderer->SetView(transform->GetPosition(), transform->GetOrientation());
		}

		if (auto camera = activeCameraEntity->GetComponent<CameraComponent>())
		{
			renderer->SetProjection(camera->GetFov(), camera->GetNear(), camera->GetFar());
		}
	}

	for (const std::shared_ptr<Entity> &entity : entities)
	{
		renderer->DrawEntity(entity);
	}
}
