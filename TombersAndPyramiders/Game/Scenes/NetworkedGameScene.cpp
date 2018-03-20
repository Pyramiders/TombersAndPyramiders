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
#include "WoodenShortsword.h"
#include "GeneratorManager.h"
#include "GameManager.h"

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
	GameManager::getInstance()->resizeQuadTree(0, 0, 200, 200);

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 200, "sandBG.png", false);
	SpawnManager::getInstance()->generateHealth(-10, 10, "FullHealth.png", false);
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
	

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 115, "sandBG.png", false);
	AudioManager::getInstance()->playMusic(MUSIC_LEVEL_1);
>>>>>>> 5c2ae033902e886b31a700b29d0dcc98fa50e94e
>>>>>>> 59a0a113b62ddcac02a9c69d8db0b0447da35363

	for (float x = 0; x <= size; x++)
	{
		for (float y = 0; y >= -size; y--)
		{
			float column = x * scale;
			float row = y * scale;
			float floorOffset = 0.56f;
			float wallOffset = 0.0f;

<<<<<<< HEAD
			// Create a floor tile. 
			SpawnManager::getInstance ()->generateMiscSquare (column, row - (y * floorOffset), (y * -1) - 50, scale, "stoneTile.png", false);

			int xMod = (int)x % 3;
			int yMod = (int)y % 3;


			if (xMod == 0 && yMod == 0 && x != 0 && y != 0 && x != size && y != -size)
			{
				SpawnManager::getInstance ()->generateMiscSquare (column, row - (y * floorOffset), 50, scale, "table.png", true);
			}

			// Create our walls. A wall is half the size of a tile, so we need two. Each wall that gets created south of a previous wall
			// needs to have a higher z value so it ovelaps the previous wall.
			// Create top walls.
=======
			SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), (y * -1) - 50, scale, "stoneTile.png", false);

>>>>>>> 5c2ae033902e886b31a700b29d0dcc98fa50e94e
			if (y == 0)
			{
				// Create top left wall.
				if (x == 0)
				{
<<<<<<< HEAD
					SpawnManager::getInstance ()->generateMiscSquare (column, row + (scale / 2) + floorOffset, y * -1, scale, "wallTopLeft.png", true);
					SpawnManager::getInstance ()->generateMiscSquare (column - scale + wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallLeft.png", true);
=======
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallTopLeft_Edge.png", true);
>>>>>>> 5c2ae033902e886b31a700b29d0dcc98fa50e94e
				}
				// Create top right wall.
				else if (x == size)
				{
<<<<<<< HEAD
					SpawnManager::getInstance ()->generateMiscSquare (column, row + (scale / 2) + floorOffset, y * -1, scale, "wallTopRight.png", true);
					SpawnManager::getInstance ()->generateMiscSquare (column + scale - wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png", true);
					SpawnManager::getInstance ()->generateMiscSquare (column - floorOffset, row + floorOffset, (y * -1) + 0.5, scale, "barrels.png", true);
				}
				else
				{
					SpawnManager::getInstance ()->generateMiscSquare (column, row + scale, y * -1, scale, "wallTop.png", true);
=======
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallTopRight_Edge.png", true);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallHorizontal.png", true);
>>>>>>> 5c2ae033902e886b31a700b29d0dcc98fa50e94e
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
<<<<<<< HEAD
					SpawnManager::getInstance ()->generateMiscSquare (column - 3, row + scale * 2, y * -1, scale, "woodPile.png", true);
				}
				SpawnManager::getInstance ()->generateMiscSquare (column, row + (scale / 2), y * -1, scale, "wallBottom.png", true);
=======
					SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallHorizontal.png", true);
				}
>>>>>>> 5c2ae033902e886b31a700b29d0dcc98fa50e94e
			}
			// Create a left wall
			else if (x == 0)
			{
<<<<<<< HEAD
				SpawnManager::getInstance ()->generateMiscSquare (column - scale + wallOffset, row + floorOffset + scale / 2, y * -1, scale, "wallLeft.png", true);
				SpawnManager::getInstance ()->generateMiscSquare (column - scale + wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallLeft.png", true);
=======
				SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallVerticalBothEdge.png", true);
>>>>>>> 5c2ae033902e886b31a700b29d0dcc98fa50e94e
			}
			// Create a right wall.
			else if (x == size)
			{
				float wallHorizontalOffset = 0.0f;

<<<<<<< HEAD
				SpawnManager::getInstance ()->generateMiscSquare (column + scale - wallOffset, row + floorOffset + scale / 2, y * -1, scale, "wallRight.png", true);
				SpawnManager::getInstance ()->generateMiscSquare (column + scale - wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png", true);
			}
		}
	}
	SpawnManager::getInstance ()->generateWorldItem (5, -5, std::make_shared<WoodenShortsword> ());
=======
				SpawnManager::getInstance()->generateMiscSquare(column, row, y * -1, scale, "wallVerticalBothEdge.png", true);
			}
		}
	}
	*/
	SpawnManager::getInstance()->generateWorldItem(5, -5, std::make_shared<WoodenShortsword>());

	//Ai = SpawnManager::getInstance ()->generateAiCharacter (14, -15);
	//Ai2 = SpawnManager::getInstance ()->generateAiCharacter (44, -20);
	//Ai3 = SpawnManager::getInstance ()->generateAiCharacter (54, -40);
	//Ai4 = SpawnManager::getInstance ()->generateAiCharacter (14, -35);

	Camera::getActiveCamera ()->addComponent<CameraFollow> (Camera::getActiveCamera ().get ());
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