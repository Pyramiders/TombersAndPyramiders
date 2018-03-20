#include "Corridor.h"
#include "SpawnManager.h"

Corridor::Corridor(int width, int height, int xPosition, int yPosition) : m_width(width), m_height(height), m_xCoord(xPosition), m_yCoord(yPosition)
{
	m_scale = 5;
}

void Corridor::draw()
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (i == 0 && j == 0)
			{
				// top left corner
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "wallTopLeft_Edge.png", false);
			}
			else if (i == 0 && j == m_width - 1)
			{
				//top right corner
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "wallTopRight_edge.png", false);
			}
			else if (i == m_height - 1 && j == 0)
			{
				//bottom left corner
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "wallBottomLeft.png", false);
			}
			else if (i == m_height - 1 && j == m_width - 1)
			{
				//bottom right corner
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "wallBottomRight.png", false);
			}
			else if (i == 0)
			{
				//top wall
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "WallHorizontal.png", false);
			}
			else if (j == 0)
			{
				//left wall
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "wallVertical.png", false);
			}
			else if (i == m_height - 1)
			{
				//bottom wall
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "WallHorizontal.png", false);
			}
			else if (j == m_width - 1)
			{
				//right wall
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "wallVertical.png", false);
			}
			else
			{
				//floor
				SpawnManager::getInstance()->generateMiscSquare(m_xCoord * 5 + 2 + j * 5, m_yCoord * 5 - 2 - i * 5, -5, m_scale, "stoneTile_Edge.png", false);
			}

		}
	}
}