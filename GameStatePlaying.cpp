#include "GameStatePlaying.h"
#include "Application.h"
#include "GameWorld.h"
#include "RenderSystem.h"

namespace Roguelike
{
	void GameStatePlayingData::Init()
	{
		Engine::GameWorld::Instance()->Clear();

		Engine::RenderSystem::Instance()->SetMainWindow(&Application::Instance().GetWindow());

		developerLevel = std::make_shared<DeveloperLevel>();
		developerLevel->Start();

		music = std::make_unique<Music>("music");
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
		{
			Application::Instance().GetGame().QuitGame();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		Engine::GameWorld::Instance()->Update(timeDelta);
		Engine::GameWorld::Instance()->FixedUpdate(timeDelta);
		Engine::GameWorld::Instance()->LateUpdate();
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		Engine::RenderSystem::Instance()->SetMainWindow(&window);
		Engine::GameWorld::Instance()->Render();
	}
}