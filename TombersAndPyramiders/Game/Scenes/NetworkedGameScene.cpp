#include "NetworkedGameScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include "SceneTemplate.h"
#include <iostream>
#include "Camera.h"
#include "SpawnManager.h"
#include "CameraFollow.h"
#include "NetworkingManager.h"
#include <memory>
#include "GeneratorManager.h"
#include "GameManager.h"
#include "FogOfWarCamera.h"
#include "GhostCamera.h"
#include "InputManager.h"
#include "MainMenuScene.h"
#include "EquipmentIncludes.h"
#include "PhysicsManager.h"
#include "Camera.h"

bool menuVisible = false;
std::shared_ptr<SimpleSprite> escapeMenu = nullptr;

NetworkedGameScene::NetworkedGameScene ()
{

}

void NetworkedGameScene::onStart ()
{

	GameManager::getInstance()->resizeQuadTree(0, 0, PYRAMID_HEIGHT * LEVEL_OFFSET * 2, 200);

	Camera::getActiveCamera()->setActiveCamera(GameManager::getInstance()->createGameObject<FogOfWarCamera>(true));

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 1000, "ControlsBlank.png", false);

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 1000, "sandBG.png", false);
	SpawnManager::getInstance()->generateWorldItem(5, -5, std::make_shared<BaseShortsword>(
		BaseShortsword::WOODEN_SHORTSWORD_DAMAGE, BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME,
		BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION));


	Camera::getActiveCamera ()->addComponent<CameraFollow> (Camera::getActiveCamera ().get ()); //players
	AudioManager::getInstance ()->playMusic (MUSIC_LEVEL_1);
}

void NetworkedGameScene::onPause ()
{

}

void NetworkedGameScene::onEnd ()
{

}

void NetworkedGameScene::onUpdate (int ticks)
{
	if (!menuVisible)
	{
		if (InputManager::getInstance()->getKeyState(SDLK_ESCAPE) == InputManager::KeyAction::PRESSED)
		{
			menuVisible = true;
			auto cameraTransform = Camera::getActiveCamera()->getTransform();
			escapeMenu = GameManager::getInstance()->createGameObject<SimpleSprite>(false, "exitNow.png", cameraTransform->getX(), cameraTransform->getY(), 5000000, 20);
			//Create menu visibility object and store it
		}
	}
	else {
		if (InputManager::getInstance()->getKeyState(SDLK_ESCAPE) == InputManager::KeyAction::PRESSED) 
		{
			menuVisible = false;
			escapeMenu->destroy(escapeMenu);
			escapeMenu = nullptr;
			//Close menu
		}
		else if (InputManager::getInstance()->getKeyState(SDLK_RETURN) == InputManager::KeyAction::PRESSED)
		{
			PhysicsManager::getInstance()->purge();
			SpriteRendererManager::getInstance()->purge();
			NetworkingManager::getInstance()->hardReset();
			Camera::getActiveCamera()->setActiveCamera(GameManager::getInstance()->createGameObject<Camera>(true));
			SceneManager::getInstance()->pushScene(new MainMenuScene());
			//Return to menu
		}
		else {
			auto cameraTransform = Camera::getActiveCamera()->getTransform();
			escapeMenu->getTransform()->setPosition(cameraTransform->getX(), cameraTransform->getY());
			//Move menu to camera/center of screen
		}
	}
	
}