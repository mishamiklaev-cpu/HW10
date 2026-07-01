#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include "Application.h"
#include "PlayerMovementComponent.h"

namespace Roguelike
{
	Player::Player()
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject("Player");

		auto transform = gameObject->GetComponent<Engine::TransformComponent>();
		transform->SetWorldPosition(Engine::Vector2Df{ 960.0f, 540.0f });

		auto playerRenderer = gameObject->AddComponent<Engine::SpriteRendererComponent>();

		const auto* texture = Engine::ResourceSystem::Instance()->GetTextureShared("ball");
		if (texture)
		{
			playerRenderer->SetTexture(*texture);
		}

		playerRenderer->SetPixelSize(64, 64);

		auto playerCamera = gameObject->AddComponent<Engine::CameraComponent>();
		playerCamera->SetWindow(&Application::Instance().GetWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<Engine::InputComponent>();

		auto body = gameObject->AddComponent<Engine::RigidbodyComponent>();
		body->SetLinearDamping(15.0f);

		auto movement = gameObject->AddComponent<Engine::PlayerMovementComponent>();
		movement->SetSpeed(200.0f);

		auto collider = gameObject->AddComponent<Engine::SpriteColliderComponent>();

		collider->SubscribeCollision([this](Engine::Collision collision)
			{
				auto myCollider = this->gameObject->GetComponent<Engine::SpriteColliderComponent>();
				if (collision.GetFirst() != myCollider && collision.GetSecond() != myCollider)
				{
					return;
				}

				Engine::ColliderComponent* otherCollider = nullptr;
				if (collision.GetFirst() == myCollider)
				{
					otherCollider = collision.GetSecond();
				}
				else
				{
					otherCollider = collision.GetFirst();
				}

				if (otherCollider != nullptr)
				{
					auto otherObject = otherCollider->GetGameObject();
					if (otherObject != nullptr && otherObject->GetName() == "AI")
					{
						Application::Instance().GetGame().LooseGame();
					}
				}
			});
	}

	Engine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}