#pragma once

#include "GameWorld.h"
#include "GameObject.h"
#include "Vector.h"
#include "FollowComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"

namespace Roguelike
{
	class AI
	{
	public:
		AI(const Engine::Vector2Df& position, Engine::GameObject* player);
		Engine::GameObject* GetGameObject();
	private:
		Engine::GameObject* gameObject;
	};
}