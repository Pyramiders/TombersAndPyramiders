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
#include <memory>
#include <WoodenLongbow.h>

CharacterTestScene::CharacterTestScene()
{
}

void CharacterTestScene::onStart()
{
	Camera::getActiveCamera()->addComponent<CameraFollow>(Camera::getActiveCamera().get());

	const int size = 10;
	const int scale = 5;

	for (int x = -size; x < size; x++)
	{
		for (int y = -size; y < size; y++)
		{
			SpawnManager::getInstance()->generateMiscSquare(x * scale, y * scale, scale);
		}
	}

	SpawnManager::getInstance()->generateWall(0, 0, 10);

	SpawnManager::getInstance()->generateWorldItem(-5, -5, std::make_shared<WoodenLongbow>());

	setCameraFollow(SpawnManager::getInstance()->generatePlayerCharacter(20, 20));
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

void CharacterTestScene::onUpdate(int ticks)
{
}