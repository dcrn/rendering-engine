#include "DefaultScene.h"

#include "Entity.h"
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
