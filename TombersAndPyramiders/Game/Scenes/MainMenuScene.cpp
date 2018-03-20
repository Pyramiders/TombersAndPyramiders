#include "MainMenuScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include "SceneTemplate.h"
#include <iostream>
#include "InputManager.h"
#include "NetworkingManager.h"
#include "SpawnManager.h"
#include "GameManager.h"
#include "AudioManager.h"
#include "Button.h"
#include "Panel.h"

MainMenuScene::MainMenuScene()
{
	
}

void MainMenuScene::onStart()
{
	GameManager::getInstance()->createGameObject<SimpleSprite>(false, "MainMenu.png", 0, 0, -1000, 42);
	GameManager::getInstance()->createGameObject<Button>(false, -300, -350, -900, 150, 80, "Start");
	GameManager::getInstance()->createGameObject<Button>(false, -100, -350, -900, 150, 80, "Host");
	GameManager::getInstance()->createGameObject<Button>(false, 75, -350, -900, 150, 80, "Join");
	GameManager::getInstance()->createGameObject<Button>(false, 250, -350, -900, 150, 80, "Info");
	GameManager::getInstance()->createGameObject<Button>(false, 425, -350, -900, 150, 80, "Exit");
	AudioManager::getInstance()->playMusic(MUSIC_MENU);
}

void MainMenuScene::onPause()
{
}

void MainMenuScene::onEnd()
{

}

void MainMenuScene::onUpdate(int ticks)
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
	if (InputManager::getInstance()->onKeyReleased(SDLK_q))
	{
		exit(0);
	}
}