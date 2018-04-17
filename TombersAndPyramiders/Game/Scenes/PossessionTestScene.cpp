#include "PossessionTestScene.h"
#include <iostream>
#include <vector>
#include "SpawnManager.h"
#include "Camera.h"
#include "GameManager.h"
#include "AudioManager.h"

/*
New Z Rule:

-10	Floor
-1	Behind-Default
0	Default
1	Above-Default
10	Ceiling

*/

PossessionTestScene::PossessionTestScene()
{
}

void PossessionTestScene::onStart()
{
	GameManager::getInstance()->resizeQuadTree(0, 0, 200, 100);
	SpawnManager::getInstance()->generateMiscSquare(25, -25, -10, 115, "sandBG.png", false);

	const float size = 6;
	const float scale = 5;

	for (float x = 0; x <= size; x++)
	{
		for (float y = 0; y >= -size; y--)
		{
			float column = x * scale;
			float row = y * scale;
			int floorZ = -3;
			int wallZ = -2;
			int stairZ = -1;

			// For setting the floor within the bounds of the map/under the walls
			float floorOffset = 0.5 * scale;

			// Create a staircase
			if (x == 3 && y == -3)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row, stairZ, scale, "spiralStairs.png", true);
			}

	/*		float floorOffset = 0.56f;
			float wallOffset = 0.0f;*/
			//SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), (y * -1) - 50, scale, "stoneTile.png", false);

			if (y == 0)
			{
				// Create top left wall.
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallTopLeft_Edge.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column + floorOffset, row - floorOffset, floorZ - 1, scale, "stoneTile_Edge.png", false);
				}
				// Create top right wall.
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallTopRight_Edge.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column - floorOffset, row - floorOffset, floorZ, scale, "stoneTile_Edge.png", false);
				}
				// Top wall
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallHorizontal.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column, row - floorOffset, floorZ, scale, "stoneTile_Edge.png", false);
				}
			}
			// Create bottom walls.
			else if (y == -size)
			{
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallBottomLeft.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column + floorOffset, row + floorOffset, floorZ, scale, "stoneTile_Edge.png", false);
				}
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallBottomRight.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column - floorOffset, row + floorOffset, floorZ, scale, "stoneTile_Edge.png", false);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallHorizontal.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column, row + floorOffset, floorZ, scale, "stoneTile_Edge.png", false);
				}
			}
			// Create a left wall
			else if (x == 0)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallVerticalBothEdge.png", true);
				SpawnManager::getInstance()->generateMiscSquare(column + floorOffset, row, floorZ, scale, "stoneTile_Edge.png", false);
			}
			// Create a right wall.
			else if (x == size)
			{
				float wallHorizontalOffset = 0.0f;

				SpawnManager::getInstance()->generateMiscSquare(column, row, wallZ, scale, "wallVerticalBothEdge.png", true);
				SpawnManager::getInstance()->generateMiscSquare(column - floorOffset, row, floorZ, scale, "stoneTile_Edge.png", false);
			}
			else
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row, floorZ, scale, "stoneTile_Edge.png", false);
			}
		}
	}

	/*for (int x = -20; x < 21; x += 10) {
		auto bg = SpawnManager::getInstance()->generateMiscSquare(x, 0, 0, 10, "stoneTile.png", false);
		bg->getTransform()->setZ(-10);
	}
	for (int x = -20; x < 21; x += 10) {
		auto bg = SpawnManager::getInstance()->generateMiscSquare(x, 0, 0, 10, "stoneTile.png", false);
		bg->getTransform()->setZ(-10);
	}
	for (int x = -21; x < 21; x++) {
		SpawnManager::getInstance()->generateMiscSquare(x, 5, 0, 1, "stoneTile.png", true, 1.0f);
		SpawnManager::getInstance()->generateMiscSquare(x, -5, 0, 1, "stoneTile.png", true, 1.0f);
	}*/
	auto playerCharacter = SpawnManager::getInstance()->generatePlayerCharacter(5, 0);
	//auto ghostCharacter = SpawnManager::getInstance()->generateGhost(5, 0);
	SpawnManager::getInstance()->generateSingleDoor(20, -5, Door::Direction::West, Door::Mode::Closed);
	SpawnManager::getInstance()->generateBoulder(5, 0);
	//SpawnManager::getInstance()->generateAiCharacter(-10, 0);
	//SpawnManager::getInstance()->generateAiCharacter(15, 5);

	//SpawnManager::getInstance()->generateSingleDoor(-15, 0, Door::Direction::West, Door::Mode::Closed);
	//SpawnManager::getInstance()->generateSingleDoor(-5, 0, Door::Direction::East, Door::Mode::Closed);
	//SpawnManager::getInstance()->generateSingleDoor(5, 3, Door::Direction::North, Door::Mode::Closed);
	//SpawnManager::getInstance()->generateSingleDoor(15, -3, Door::Direction::South, Door::Mode::Closed);

	Camera::getActiveCamera()->addComponent<CameraFollow>((GameObject*)Camera::getActiveCamera().get())->setToFollow(playerCharacter);
	AudioManager::getInstance()->playMusic(MUSIC_LEVEL_1);
}

void PossessionTestScene::onPause()
{
}

void PossessionTestScene::onEnd()
{

}

void PossessionTestScene::onUpdate(int ticks)
{
}