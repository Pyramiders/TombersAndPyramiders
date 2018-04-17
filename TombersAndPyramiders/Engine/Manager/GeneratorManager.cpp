#pragma once

#include "GeneratorManager.h"
#include <vector>
#include "GameManager.h"
#include "Randomize.h"

GeneratorManager* GeneratorManager::s_instance;

GeneratorManager* GeneratorManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new GeneratorManager();
	return s_instance;
}

/*std::shared_ptr<GeneratorManager> GeneratorManager::s_instance;

std::shared_ptr<GeneratorManager> GeneratorManager::getInstance()
{
	if (s_instance == nullptr)
		s_instance = GameManager::getInstance()->createGameObject<GeneratorManager>(true);
	return s_instance;
}*/

GeneratorManager::GeneratorManager()
{
	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			worldMatrix[i][j] = 0;
		}
	}
}

void GeneratorManager::generateLevel(int width, int height, int detailLevel, int level) 
{
	std::shared_ptr<Level> temp = std::make_shared<Level>();
	levels.push_back(temp);
	m_worldTree = std::make_shared<BinaryTree>(width, height);
	m_worldTree->partition(level, detailLevel);
	m_worldTree->makeCorridors(levels[level]->rooms);
	showWorld();
}

void GeneratorManager::drawLevel(int level) {
	
	//draw corridor walls and floor tiles if intersecting nothing or room walls,
	
	for (int i = 0; i < levels[level]->corridors.size(); i++) {
		levels[level]->corridors[i]->draw();
	}

	int exitRoom = Randomize::Random(0, levels[level]->rooms.size() - 1);
	levels[level]->rooms[exitRoom]->m_exit = true;
	for (int i = 0; i < levels[level]->rooms.size(); i++) {
		levels[level]->rooms[i]->draw();
	}

	//draw/spawn items
	
}

void GeneratorManager::recordRoom(std::shared_ptr<Room> r)
{
	for (int i = 0; i < r->m_height; i++)
	{
		for (int j = 0; j < r->m_width; j++)
		{
			if (j == 0 || j == r->m_width - 1 || i == 0 || i == r->m_height - 1) 
			{
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 2;
			}
			else {
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 1;
			}
		}
	}
}

void GeneratorManager::recordCorridor(std::shared_ptr<Corridor> c)
{
	for (int i = 0; i < c->m_height; i++)
	{
		for (int j = 0; j < c->m_width; j++)
		{
			int temp = worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i];
			if (temp == 2 && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 5;
			else if (temp == 2 && ((i == 0 && j == c->m_width - 1) || (j == 0 && i == c->m_height - 1) || (i == 0 && j == 0) || (j == c->m_width - 1 && i == c->m_height - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 5;
			}
			else if (temp == 2)
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 7;
			}else if ((temp == 8 || temp == 9) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 7;
			}
			else if (temp == 0 && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 8;
			}
			else if (temp == 0 && ((i == 0 && j == c->m_width - 1) || (j == 0 && i == c->m_height - 1) || (i == 0 && j == 0) || (j == c->m_width - 1 && i == c->m_height - 1) ))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 9;
			}
			else if (temp == 0) 
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 7;
			}
		}
	}
}

void GeneratorManager::showWorld() 
{
	for (int i = 0; i < WORLD_HEIGHT; i++)
	{
		for (int j = 0; j < WORLD_WIDTH; j++)
		{
			std::cout << worldMatrix[j][i] << " ";
		}
		std::cout << std::endl;
	}
}