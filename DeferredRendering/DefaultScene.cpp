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
	AddEntity(CreateCubeEntity());
}

std::shared_ptr<Entity> DefaultScene::CreateCubeEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();

	auto mesh = std::make_shared<MeshComponent>();
	mesh->SetPrimitiveShape(PrimitiveShape::Cube);

	auto transform = std::make_shared<TransformComponent>();

	entity->AddComponent(transform);
	entity->AddComponent(mesh);
	entity->AddComponent(std::make_shared<SpinnerComponent>());

	return entity;
}
