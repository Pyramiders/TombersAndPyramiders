#include "CharacterTestScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include <iostream>
#include "Camera.h"
#include "MovingSquare.h"
#include "MiscSquare.h"
#include <vector>
#include "SpawnManager.h"

std::shared_ptr<PlayerCharacter> player = nullptr;

CharacterTestScene::CharacterTestScene()
{
}

void CharacterTestScene::onStart()
{
	Camera::getActiveCamera()->addComponent(std::make_shared<CameraFollow>(Camera::getActiveCamera().get()));

	for (int x = -5; x < 5; x++)
	{
		for (int y = -5; y < 5; y++)
		{
			SpawnManager::getInstance()->generateMiscSquare(x * 5, y * 5, 5);
		}
	}

	player = SpawnManager::getInstance()->generateSimpleCharacter(15, 5);
	setCameraFollow(player);
}

void CharacterTestScene::setCameraFollow(std::shared_ptr<GameObject> toFollow)
{
	Camera::getActiveCamera()->getComponent<CameraFollow>()->setToFollow(toFollow);
}

void CharacterTestScene::onPause()
{
}

void CharacterTestScene::onEnd()
{

}

int counter = 0;
void CharacterTestScene::onUpdate(int ticks)
{
	if (counter++ == 60)
	{
		player->destroy(player);
		player = nullptr;
	}
	if (counter == 120)
	{
		player = SpawnManager::getInstance()->generateSimpleCharacter(-10, 5);
		setCameraFollow(player);
	}
}