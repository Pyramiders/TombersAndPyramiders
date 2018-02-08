#include "CameraTestScene.h"
#include "GLHeaders.h"
#include "SpriteRendererManager.h"
#include "Shader.h"
#include "SharedConstants.h"
#include <iostream>
#include "Camera.h"
#include <vector>
#include "SpawnManager.h"

CameraTestScene::CameraTestScene()
{
}

void CameraTestScene::onStart()
{
	//Dummy: Load a shit ton of tiles to give us a background to prove cameraFollow
	for (int x = -5; x < 5; x++)
	{
		for (int y = -5; y < 5; y++)
		{
			SpawnManager::getInstance()->generateMiscSquare(x * 5, y * 5, 5);
		}
	}

	CameraFollow* cameraFollow = new CameraFollow(Camera::getActiveCamera());
	Camera::getActiveCamera()->addComponent(cameraFollow);
	cameraFollow->setToFollow(SpawnManager::getInstance()->generateMovingSquare(0, 0));
}

void CameraTestScene::onPause()
{
}

void CameraTestScene::onEnd()
{

}

void CameraTestScene::onUpdate(int ticks)
{
}