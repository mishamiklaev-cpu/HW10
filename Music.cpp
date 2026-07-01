#include "Music.h"

namespace Roguelike
{
	Music::Music(const std::string& resourceName)
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject("MusicManager");
		audioComponent = gameObject->AddComponent<Engine::AudioComponent>();

		const sf::SoundBuffer* buffer = Engine::ResourceSystem::Instance()->GetSoundBufferShared(resourceName);
		if (buffer)
		{
			audioComponent->SetAudio(*buffer);
			audioComponent->SetLoop(true);
			audioComponent->SetVolume(50.0f);
			audioComponent->Play();
		}
		else
		{
			std::cout << "Music buffer not found: " << resourceName << std::endl;
		}
	}

	Music::~Music()
	{
		if (audioComponent) audioComponent->Stop();
		Engine::GameWorld::Instance()->DestroyGameObject(gameObject);
	}

	void Music::Play() { if (audioComponent) audioComponent->Play(); }
	void Music::Stop() { if (audioComponent) audioComponent->Stop(); }
}