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

CharacterTestScene::CharacterTestScene()
{
}

void CharacterTestScene::onStart()
{
	CameraFollow* cameraFollow = new CameraFollow(Camera::getActiveCamera());
	Camera::getActiveCamera()->addComponent(cameraFollow);

	for (int x = -5; x < 5; x++)
	{
		for (int y = -5; y < 5; y++)
		{
			SpawnManager::getInstance()->generateMiscSquare(x * 5, y * 5, 5);
		}
	}

	setCameraFollow(SpawnManager::getInstance()->generateSimpleCharacter(15, 5));
}

void CharacterTestScene::setCameraFollow(std::shared_ptr<GameObject> toFollow)
{
	Camera::getActiveCamera()->getComponent<CameraFollow*>()->setToFollow(toFollow);
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