#include "DeveloperLevel.h"
#include <ResourceSystem.h>

namespace Roguelike
{
	void DeveloperLevel::Start()
	{
		Engine::ResourceSystem::Instance()->LoadTextureMap("level_walls", "assets/walls.png", sf::Vector2u(128, 128), 4);
		Engine::ResourceSystem::Instance()->LoadTextureMap("level_floors", "assets/floors.png", sf::Vector2u(128, 128), 4);
		Engine::ResourceSystem::Instance()->LoadTextureMap("AI", "assets/enemy.png", sf::Vector2u(100, 100), 1);
		Engine::ResourceSystem::Instance()->LoadTexture("ball", "assets/ball.png");
		Engine::ResourceSystem::Instance()->LoadSoundBuffer("music", "assets/music.ogg");

		int width = 15;
		int height = 15;
		float tileSize = 128.0f;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				Engine::Vector2Df pos = { x * tileSize, y * tileSize };
				floors.push_back(std::make_unique<Floor>(pos, 0));
			}
		}

		for (int y = 0; y < height + 1; y++)
		{
			walls.push_back(std::make_unique<Wall>(Engine::Vector2Df{ 0.0f, y * tileSize }, 0));
			walls.push_back(std::make_unique<Wall>(Engine::Vector2Df{ width * tileSize, y * tileSize }, 0));
		}
		for (int x = 0; x < width + 1; x++)
		{
			walls.push_back(std::make_unique<Wall>(Engine::Vector2Df{ x * tileSize, 0.0f }, 0));
			walls.push_back(std::make_unique<Wall>(Engine::Vector2Df{ x * tileSize, height * tileSize }, 0));
		}

		player = std::make_shared<Player>();
		auto playerTransform = player->GetGameObject()->GetComponent<Engine::TransformComponent>();
		playerTransform->SetWorldPosition(Engine::Vector2Df{ width / 2.0f * tileSize, height / 2.0f * tileSize });

		ai = std::make_shared<AI>(Engine::Vector2Df{ width / 3.0f * tileSize, height / 3.0f * tileSize }, player->GetGameObject());

	}

	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		Engine::GameWorld::Instance()->Clear();
		player.reset();
		ai.reset();
		music.reset();
		walls.clear();
		floors.clear();
	}
}