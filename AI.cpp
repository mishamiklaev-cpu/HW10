#include "AI.h"
#include "ResourceSystem.h"

namespace Roguelike
{
	AI::AI(const Engine::Vector2Df& position, Engine::GameObject* player)
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject("AI");
		auto transform = gameObject->GetComponent<Engine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<Engine::SpriteRendererComponent>();
		renderer->SetTexture(*Engine::ResourceSystem::Instance()->GetTextureMapElementShared("AI", 0));
		renderer->SetPixelSize(100, 100);

		auto rigidbody = gameObject->AddComponent<Engine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto follower = gameObject->AddComponent<Engine::FollowComponent>();
		follower->SetTarget(player);
		follower->SetSpeed(120.0f);
		follower->SetDetectionRadius(350.0f);

		auto collider = gameObject->AddComponent<Engine::SpriteColliderComponent>();
	}

	Engine::GameObject* AI::GetGameObject()
	{
		return gameObject;
	}
}