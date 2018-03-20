#include "Room.h"
#include "SpawnManager.h"

Room::Room(int width, int height, int xPosition, int yPosition, bool exit) : m_width(width), m_height(height), m_xCoord(xPosition), m_yCoord(yPosition), m_exit(exit),
		ComplexSprite(generateComplexSpriteInfo(), 0, -2, 10, 5)
{
	m_scale = 5;
}

void Room::draw() 
{
	std::cout << m_xCoord << " " << m_yCoord << std::endl;
	std::cout << m_width << " " << m_height << std::endl;
	//algorithm for drawing a room 
	//SpawnManager::getInstance()->generateMiscSquare(m_xCoord+2, m_yCoord-2, 10, m_scale, "stoneTile.png", true);

	for (int i = 0; i < m_height; i++) 
	{
		for (int j = 0; j < m_width; j++) 
		{	
			bool skip = false;
			for (int k = 0; k < doorsX.size(); k++)
			{
				if (m_yCoord - i == doorsY[k] && m_xCoord + j == doorsX[k])
				{
					if (i == 0)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, Door::Direction::West, Door::Mode::Closed);
					}
					else if (j == 0)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, Door::Direction::South, Door::Mode::Closed);
					}
					else if (i == m_height - 1)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, Door::Direction::West, Door::Mode::Closed);
					}
					else if (j == m_width - 1)
					{
						SpawnManager::getInstance()->generateSingleDoor(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, Door::Direction::North, Door::Mode::Closed);
					}
					
					skip = true;
				}
			}
			if (!skip)
			{
				if (i == 0 && j == 0)
				{
					// top left corner
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallTopLeft_Edge.png", true);
				}
				else if (i == 0 && j == m_width - 1)
				{
					//top right corner
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallTopRight_Edge.png", true);
				}
				else if (i == m_height - 1 && j == 0)
				{
					//bottom left corner
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallBottomLeft.png", true);
				}
				else if (i == m_height - 1 && j == m_width - 1)
				{
					//bottom right corner
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallBottomRight.png", true);
				}
				else if (i == 0)
				{
					//top wall
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "WallHorizontal.png", true, m_scale, m_scale/4.5);
				}
				else if (j == 0)
				{
					//left wall
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallVertical.png", true, m_scale/4.5, m_scale);
				}
				else if (i == m_height - 1)
				{
					//bottom wall
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallHorizontal.png", true, m_scale, m_scale /4.5);
				}
				else if (j == m_width - 1)
				{
					//right wall
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "wallVertical.png", true, m_scale/4.5, m_scale);
				}
				else
				{
					//floor
					SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -1, m_scale, "stoneTile_Edge.png", false);
				}
			}
			
		}
	}
	if (m_exit) {
		//draw stairs
		int x = rand() % m_width/2 + ceil(m_width/4);
		int y = rand() % m_height/2 + ceil(m_height/4);
		SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + x * 5, m_yCoord * 5 - 2 - y * 5, 0, m_scale, "spiralStairs.png", true, 3.0f);

	}
}

std::shared_ptr<ComplexSpriteinfo> Room::generateComplexSpriteInfo()
{
	std::shared_ptr<ComplexSpriteinfo> spriteInfo = std::make_shared<ComplexSpriteinfo>();

	spriteInfo->addInfo("stoneTile.png", 1, 1);

	return spriteInfo;
}