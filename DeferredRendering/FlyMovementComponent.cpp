#include "FlyMovementComponent.h"

#include "Entity.h"
#include "TransformComponent.h"

void FlyMovementComponent::Update(Entity* parent, float deltaTime)
{
	parent->GetComponent<TransformComponent>();
}
