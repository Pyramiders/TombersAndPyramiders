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
#include "AudioManager.h"
#include "EquipmentIncludes.h"

using namespace std;


CharacterTestScene::CharacterTestScene()
{
}

void CharacterTestScene::onStart()
{
	Camera::getActiveCamera()->addComponent<CameraFollow>(Camera::getActiveCamera().get());

	const float size = 12;
	const float scale = 5;
	const int ai = 100;
	SpawnManager::getInstance()->generateMiscSquare(25, -25, -100, 115, "sandBG.png", false);

	/*for (int x = 0; x <= ai; x++)
	{
		
			SpawnManager::getInstance()->generateAiCharacter(x, 0);
			for (int y = 0; y <= ai; y++)
			{
				SpawnManager::getInstance()->generateAiCharacter(0, y);
			}
	

	}*/
	

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
			SpawnManager::getInstance()->generateMiscSquare(column, row - (y * floorOffset) , (y * -1) - 50, scale, "stoneTile.png", false);

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
				SpawnManager::getInstance()->generateMiscSquare(column, row + (scale / 2) , y * -1, scale, "wallBottom.png", true);
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
	SpawnManager::getInstance()->generateWorldItem(5, -5, std::make_shared<BaseLongbow>(
		BaseLongbow::WOODEN_LONGBOW_DAMAGE, BaseLongbow::WOODEN_LONGBOW_IMAGE_NAME, 
		BaseLongbow::WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME, BaseLongbow::WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION));

	player = SpawnManager::getInstance()->generatePlayerCharacter(15, -10);
	Ai = SpawnManager::getInstance()->generateAiCharacter(30000, 14, -18);
	Ai2 = SpawnManager::getInstance()->generateAiCharacter(30001, 13, -40);
	Ai3 = SpawnManager::getInstance()->generateAiCharacter(30002, 50, -50);
	Ai4 = SpawnManager::getInstance()->generateAiCharacter(30003, 50, -20);

	//setCameraFollow(player);
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