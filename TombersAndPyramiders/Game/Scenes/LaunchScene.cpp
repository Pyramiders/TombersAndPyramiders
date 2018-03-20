#include "LaunchScene.h"
#include "InputManager.h"
#include "NetworkingManager.h"
#include "SpawnManager.h"
#include "GameManager.h"
#include "AudioManager.h"

LaunchScene::LaunchScene()
{

}

void LaunchScene::onStart()
{
	SpawnManager::getInstance();
	GameManager::getInstance()->createGameObject<SimpleSprite>(false, "LandingPage.png", 0, 0, -1000, 42);
	AudioManager::getInstance()->playMusic();
	SpawnManager::getInstance()->sendStartPacket();
}

void LaunchScene::onPause()
{
}

void LaunchScene::onEnd()
{
}

void LaunchScene::onUpdate(int ticks)
{
	if (InputManager::getInstance()->onKeyReleased(SDLK_j))
	{
		NetworkingManager::getInstance()->createClient();
	}
	if (InputManager::getInstance()->onKeyReleased(SDLK_h))
	{
		NetworkingManager::getInstance()->createHost();
	}
	if (InputManager::getInstance()->onKeyReleased(SDLK_k))
	{
		if (NetworkingManager::getInstance()->startGame()) {
			SpawnManager::getInstance()->sendStartPacket();
		}
	}
}