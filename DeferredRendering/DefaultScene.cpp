#include "DefaultScene.h"

#include "CameraComponent.h"
#include "Entity.h"
#include "FlyMovementComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

class SpinnerComponent : public Component
{
public:
	constexpr static const char* TYPE = "SpinnerComponent";
	void Update(Entity* parent, float deltaTime) override
	{
		if (auto transform = parent->GetComponent<TransformComponent>())
		{
			rotation += deltaTime;
			transform->SetOrientation(glm::angleAxis(rotation, glm::vec3(0.0f, 0.0f, 1.0f)));
		}
	}

	float rotation = 0.0f;
};

DefaultScene::DefaultScene()
{
	AddEntity(CreateCubeEntity(glm::vec3(5.0f, 0.0f, 0.0f)));
	AddEntity(CreateCubeEntity(glm::vec3(-5.0f, 0.0f, 0.0f)));
	AddEntity(CreateCubeEntity(glm::vec3(0.0f, 5.0f, 0.0f)));
	AddEntity(CreateCubeEntity(glm::vec3(0.0f, -5.0f, 0.0f)));
	AddEntity(CreateCubeEntity(glm::vec3(0.0f, 0.0f, 5.0f)));

	glm::quat a = glm::angleAxis(glm::radians(180.0f), glm::normalize(glm::vec3(-1.0f)));
	glm::quat b = glm::angleAxis(glm::radians(180.0f), glm::normalize(glm::vec3(-1.0f)));
	glm::quat c = a * b;
	

	AddEntity(CreateCameraEntity(
		glm::vec3(20.0f),
		glm::quat(1.0f,glm::normalize(glm::vec3(-1.0f)))
	));
}

std::shared_ptr<Entity> DefaultScene::CreateCameraEntity(glm::vec3 initialPosition, glm::quat initialOrientation)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	auto camera = std::make_shared<CameraComponent>();
	camera->SetActive(true);

	auto transform = std::make_shared<TransformComponent>();
	transform->SetPosition(initialPosition);
	transform->SetOrientation(initialOrientation);

	auto flyMovement = std::make_shared<FlyMovementComponent>();

	entity->AddComponent(transform);
	entity->AddComponent(camera);
	entity->AddComponent(flyMovement);

	return entity;
}

std::shared_ptr<Entity> DefaultScene::CreateCubeEntity(const glm::vec3 &initialPosition)
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	auto mesh = std::make_shared<MeshComponent>();
	mesh->SetPrimitiveShape(PrimitiveShape::Cube);

	auto transform = std::make_shared<TransformComponent>();
	transform->SetPosition(initialPosition);

	entity->AddComponent(transform);
	entity->AddComponent(mesh);
	entity->AddComponent(std::make_shared<SpinnerComponent>());

	return entity;
}
