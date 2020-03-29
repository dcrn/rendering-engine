#include "DefaultScene.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

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

	return entity;
}
