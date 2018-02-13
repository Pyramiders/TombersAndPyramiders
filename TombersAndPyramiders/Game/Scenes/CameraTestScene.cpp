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
	for (int x = -50; x < 50; x++)
	{
		for (int y = -50; y < 0; y++)
		{
			SpawnManager::getInstance()->generateMiscSquare(x * 5, y * 5, 5);
		}
	}

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