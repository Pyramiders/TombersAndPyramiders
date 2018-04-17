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
#include "EquipmentIncludes.h"

std::map<int, shared_ptr<Character>> players;
std::shared_ptr<Character> Ai = nullptr;
std::shared_ptr<Character> Ai2 = nullptr;
std::shared_ptr<Character> Ai3 = nullptr;
std::shared_ptr<Character> Ai4 = nullptr;

NetworkedGameScene::NetworkedGameScene ()
{

}

void NetworkedGameScene::onStart ()
{

	GameManager::getInstance()->resizeQuadTree(0, 0, PYRAMID_HEIGHT * LEVEL_OFFSET * 2, 200);

	Camera::getActiveCamera()->setActiveCamera(GameManager::getInstance()->createGameObject<FogOfWarCamera>(true));


	//time_t mapSeedID = time(NULL);
	//srand(mapSeedID);
	//GeneratorManager::getInstance()->generateLevel(30, 30, 2, 0);
	
	//GeneratorManager::getInstance()->drawLevel(0);

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 1000, "sandBG.png", false);
	/*
	const float scale = 5;

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 115, "sandBG.png", false);

	/*std::vector<std::vector<int>> level{ {0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0} };

	std::vector<std::vector<int>> level{{ 1,5,5,5,5,2,9,1,5,5,5,5,5,5,5,5,5,2 } ,
										{ 7,0,0,0,0,3,5,4,0,0,0,0,0,0,0,0,0,8 } ,
										{ 7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8 } ,
										{ 7,0,0,0,0,1,6,2,0,0,0,0,0,0,0,0,0,8 } ,
										{ 3,6,2,0,1,4,9,7,0,0,0,0,0,0,0,0,0,8 } ,
										{ 9,9,7,0,8,9,9,7,0,0,0,0,0,0,0,0,0,8 } ,
										{ 1,5,4,0,3,5,2,7,0,0,0,0,0,0,0,0,0,8 } ,
										{ 7,0,0,0,0,0,8,7,0,0,0,0,0,0,0,0,0,8 } ,
										{ 7,0,0,0,0,0,8,3,6,6,6,6,6,2,0,0,0,8 } ,
										{ 7,0,0,0,0,0,8,9,9,9,9,9,9,7,0,0,0,8 } ,
										{ 3,6,6,6,6,6,4,9,9,9,9,9,9,7,0,0,0,8 } ,
										{ 1,5,5,5,5,5,5,5,5,5,5,5,5,4,0,0,0,8 } ,
										{ 7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8 } ,
										{ 7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8 } ,
										{ 3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,4 } };

	for (int i = 0; i < level.size(); i++)
	{
		for (int j = 0; j < level[i].size(); j++)
		{
			switch (level[i][j]) {
			case 0:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "stoneTile.png", true);
				break;
			case 1:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallTopLeft.png", true);
				break;
			case 2:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallTopRight.png", true);
				break;
			case 3:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallBottomLeft.png", true);
				break;
			case 4:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallBottomRight.png", true);
				break;
			case 5:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallTop.png", true);
				break;
			case 6:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallBottom.png", true);
				break;
			case 7:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallLeft.png", true);
				break;
			case 8:
				SpawnManager::getInstance()->generateMiscSquare(j*scale, -i*scale, -10, scale, "wallRight.png", true);
				break;
			}
		}
	}

	*/

	/*
	const float size = 12;
	const float scale = 5;

<<<<<<< HEAD

	SpawnManager::getInstance ()->generateMiscSquare (25, -25, -100, 115, "sandBG.png", false);
=======
	

=======
>>>>>>> 695e64bd65f0ada673fba6bee0a2bc68d0f8c344
	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 115, "sandBG.png", false);
	AudioManager::getInstance()->playMusic(MUSIC_LEVEL_1);

	for (float x = 0; x <= size; x++)
	{
		for (float y = 0; y >= -size; y--)
		{
			float column = x * scale;
			float row = y * scale;
			float floorOffset = 0.56f;
			float wallOffset = 0.0f;

			SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), (y * -1) - 50, scale, "stoneTile.png", false);

			if (y == 0)
			{
				// Create top left wall.
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallTopLeft_Edge.png", true);
				}
				// Create top right wall.
				else if (x == size)
				{

					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallTopRight_Edge.png", true);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallHorizontal.png", true);
				}
			}
			// Create bottom walls.
			else if (y == -size)
			{
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallBottomLeft.png", true);
				}
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallBottomRight.png", true);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallHorizontal.png", true);
				}
			}
			// Create a left wall
			else if (x == 0)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallVerticalBothEdge.png", true);
			}
			// Create a right wall.
			else if (x == size)
			{
				float wallHorizontalOffset = 0.0f;


				SpawnManager::getInstance ()->generateMiscSquare (column + scale - wallOffset, row + floorOffset + scale / 2, y * -1, scale, "wallRight.png", true);
				SpawnManager::getInstance ()->generateMiscSquare (column + scale - wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png", true);
			}
		}
	}
	SpawnManager::getInstance ()->generateWorldItem (5, -5, std::make_shared<WoodenShortsword> ());
				SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallVerticalBothEdge.png", true);
			}
		}
	}
	*/
	SpawnManager::getInstance()->generateWorldItem(5, -5, std::make_shared<BaseShortsword>(
		BaseShortsword::WOODEN_SHORTSWORD_DAMAGE, BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME,
		BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION));

	//Ai = SpawnManager::getInstance()->generateAiCharacter(14, -18);
	//Ai2 = SpawnManager::getInstance()->generateAiCharacter(13, -40);
	//Ai3 = SpawnManager::getInstance()->generateAiCharacter(50, -50);
	//Ai4 = SpawnManager::getInstance()->generateAiCharacter(50, -20);



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
}