#include "OldTestScene.h"
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
#include "EquipmentIncludes.h"

std::shared_ptr<Character> player1 = nullptr;
std::shared_ptr<Character> player2 = nullptr;
std::shared_ptr<Character> AiA = nullptr;
std::shared_ptr<Character> AiB = nullptr;
std::shared_ptr<Character> AiC = nullptr;
std::shared_ptr<Character> AiD = nullptr;

OldTestScene::OldTestScene()
{

}

void OldTestScene::onStart()
{
	const float size = 12;
	const float scale = 5;

	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 115, "sandBG.png", false);

	for (float x = 0; x <= size; x++)
	{
		for (float y = 0; y >= -size; y--)
		{
			float column = x * scale;
			float row = y * scale;

			// The offsets are to allow the tile art to overlap.
			float floorOffset = 0.56f;
			float wallOffset = 1.25f;

			// Create a floor tile. 
			SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), (y * -1) - 50, scale, "stoneTile.png", false);

			int xMod = (int)x % 3;
			int yMod = (int)y % 3;


			if (xMod == 0 && yMod == 0 && x != 0 && y != 0 && x != size && y != -size)
			{
				SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset), 50, scale, "table.png", true);
			}

			// Create our walls. A wall is half the size of a tile, so we need two. Each wall that gets created south of a previous wall
			// needs to have a higher z value so it ovelaps the previous wall.
			// Create top walls.
			if (y == 0)
			{
				// Create top left wall.
				if (x == 0)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row + (scale / 2) + floorOffset, y * -1, scale, "wallTopLeft.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column - scale + wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallLeft.png", true);
				}
				// Create top right wall.
				else if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row + (scale / 2) + floorOffset, y * -1, scale, "wallTopRight.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column + scale - wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png", true);
					SpawnManager::getInstance()->generateMiscSquare(column - floorOffset, row + floorOffset, (y * -1) + 0.5, scale, "barrels.png", true);
				}
				else
				{
					SpawnManager::getInstance()->generateMiscSquare(column, row + scale, y * -1, scale, "wallTop.png", true);
				}
			}
			// Create bottom walls.
			else if (y == -size)
			{
				if (x == size)
				{
					SpawnManager::getInstance()->generateMiscSquare(column - 3, row + scale * 2, y * -1, scale, "woodPile.png", true);
				}
				SpawnManager::getInstance()->generateMiscSquare(column, row + (scale / 2), y * -1, scale, "wallBottom.png", true);
			}
			// Create a left wall
			else if (x == 0)
			{
				SpawnManager::getInstance()->generateMiscSquare(column - scale + wallOffset, row + floorOffset + scale / 2, y * -1, scale, "wallLeft.png", true);
				SpawnManager::getInstance()->generateMiscSquare(column - scale + wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallLeft.png", true);
			}
			// Create a right wall.
			else if (x == size)
			{
				float wallHorizontalOffset = scale;

				SpawnManager::getInstance()->generateMiscSquare(column + scale - wallOffset, row + floorOffset + scale / 2, y * -1, scale, "wallRight.png", true);
				SpawnManager::getInstance()->generateMiscSquare(column + scale - wallOffset, row + floorOffset, (y * -1) + 0.5, scale, "wallRight.png", true);
			}
		}
	}

	SpawnManager::getInstance()->generateWorldItem(5, -5, std::make_shared<BaseShortsword>(
		BaseShortsword::WOODEN_SHORTSWORD_DAMAGE, BaseShortsword::WOODEN_SHORTSWORD_IMAGE_NAME, 
		BaseShortsword::WOODEN_SHORTSWORD_DESTROY_ON_COLLISION));

	//AiA = SpawnManager::getInstance()->generateAiCharacter(14, -15);
	//AiB = SpawnManager::getInstance()->generateAiCharacter(44, -20);
	//AiC = SpawnManager::getInstance()->generateAiCharacter(54, -40);
	//AiD = SpawnManager::getInstance()->generateAiCharacter(14, -35);

	SpawnManager::getInstance()->generateSingleDoor(10, -10, Door::Direction::West, Door::Mode::Closed);

	Camera::getActiveCamera()->addComponent<CameraFollow>(Camera::getActiveCamera().get());
	
	
	player1 = SpawnManager::getInstance()->generatePlayerCharacter(1, 0, 0);
	setCameraFollow(player1);
}

void OldTestScene::onPause()
{

}

void OldTestScene::onEnd()
{

}

void OldTestScene::onUpdate(int ticks)
{
}