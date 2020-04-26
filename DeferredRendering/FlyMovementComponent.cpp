#include "FlyMovementComponent.h"

#include "Engine.h"
#include "Entity.h"
#include "InputManager.h"
#include "TransformComponent.h"

void FlyMovementComponent::Update(Entity* parent, float deltaTime)
{
	auto transform = parent->GetComponent<TransformComponent>();
	if (!transform)
	{
		return;
	}


	glm::vec3 pos = transform->GetPosition();
	glm::quat quat = transform->GetOrientation();
	glm::vec3 dir = glm::normalize(glm::vec3(quat.x, quat.y, quat.z));

	if (Engine::Instance.GetInputManager()->GetKeyState(KeyCode::Space) == KeyState::Pressed)
	{
		pos += glm::vec3(0.0f, 0.0f, speed * deltaTime);
	}
	if (Engine::Instance.GetInputManager()->GetKeyState(KeyCode::LeftCtrl) == KeyState::Pressed)
	{
		pos += glm::vec3(0.0f, 0.0f, -speed * deltaTime);
	}
	if (Engine::Instance.GetInputManager()->GetKeyState(KeyCode::W) == KeyState::Pressed)
	{
		pos += dir * speed * deltaTime;
	}
	if (Engine::Instance.GetInputManager()->GetKeyState(KeyCode::S) == KeyState::Pressed)
	{
		pos += dir * -speed * deltaTime;
	}

	// TODO: Use quat roll for left-right movement
	if (Engine::Instance.GetInputManager()->GetKeyState(KeyCode::A) == KeyState::Pressed)
	{
		pos += glm::cross(dir, glm::vec3(0.0f, 0.0f, 1.0f)) * -speed * deltaTime;
	}
	if (Engine::Instance.GetInputManager()->GetKeyState(KeyCode::D) == KeyState::Pressed)
	{
		pos += glm::cross(dir, glm::vec3(0.0f, 0.0f, 1.0f)) * speed * deltaTime;
	}

	transform->SetPosition(pos);
}

float FlyMovementComponent::GetSpeed() const
{
	return speed;
}

void FlyMovementComponent::SetSpeed(float speed)
{
	this->speed = speed;
}
