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
			worldMatrix[i][j] = -1;
		}
	}
}

void GeneratorManager::reset()
{
	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			worldMatrix[i][j] = -1;
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

	if (level != 0) {
		int spawnRoom = Randomize::Random(0, levels[level]->rooms.size() - 1);
		levels[level]->rooms[spawnRoom]->m_spawn = true;
	}

	for (int i = 0; i < levels[level]->rooms.size(); i++) {
		levels[level]->rooms[i]->draw();
	}	
}

void GeneratorManager::recordRoom(std::shared_ptr<Room> r)
{
	for (int i = 0; i < r->m_height; i++)
	{
		for (int j = 0; j < r->m_width; j++)
		{
			if (i == 0 && j == 0)
			{
				// top left corner
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 9;
			}
			else if (i == 0 && j == r->m_width - 1)
			{
				//top right corner
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 9;
			}
			else if (i == r->m_height - 1 && j == 0)
			{
				//bottom left corner
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 9;
			}
			else if (i == r->m_height - 1 && j == r->m_width - 1)
			{
				//bottom right corner
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 9;
			}
			else if (i == 0)
			{
				//top wall
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 1;
			}
			else if (j == 0)
			{
				//left wall
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 4;
			}
			else if (i == r->m_height - 1)
			{
				//bottom wall
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 3;
			}
			else if (j == r->m_width - 1)
			{
				//right wall
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 2;
			}
			else
			{
				worldMatrix[r->m_xCoord + WORLD_WIDTH / 2 + j][-(r->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
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
			if ((temp == 2 || temp == 1 || temp == 3 || temp == 4 || temp == 9) && (i == 0 && j != 0 && j != c->m_width - 1))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 12;
			}
			else if((temp == 2 || temp == 1 || temp == 3 || temp == 4 || temp == 9) && (j == 0 && i != 0 && i != c->m_height - 1)){
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 15;
			}
			else if ((temp == 2 || temp == 1 || temp == 3 || temp == 4 || temp == 9) && (j == c->m_width - 1 && i != 0 && i != c->m_height - 1)) {
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 13;
			}
			else if ((temp == 2 || temp == 1 || temp == 3 || temp == 4 || temp == 9) && (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)) {
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 14;
			}			
			else if ((temp == 2 || temp == 4 || temp == 1 || temp == 3 || temp == 9) && ((i == 0 && j == c->m_width - 1) || (i == 0 && j == 0)) && c->m_height == 3)
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 12;
			}
			else if ((temp == 2 || temp == 4 || temp == 1 || temp == 3 || temp == 9) && ((j == 0 && i == c->m_height - 1) || (j == c->m_width - 1 && i == c->m_height - 1)) && c->m_height == 3)
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 14;
			}
			else if ((temp == 1 || temp == 3 || temp == 2 || temp == 4 || temp == 9) && ((j == 0 && i == c->m_height - 1) || (i == 0 && j == 0)) && c->m_width == 3)
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 15;
			}
			else if ((temp == 1 || temp == 3 || temp == 2 || temp == 4 || temp == 9) && ((i == 0 && j == c->m_width - 1) || (j == c->m_width - 1 && i == c->m_height - 1)) && c->m_width == 3)
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 13;
			}
			else if (temp == 1 || temp == 2 || temp == 3 || temp == 4)
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
			}
			else if ((temp == 10) && ((j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 5;
			}
			else if ((temp == 10) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 6;
			}
			else if ((temp == 10) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 7;
			}
			else if ((temp == 10) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 8;
			}
			/*
			else if ((temp == 5) && ((j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
			}
			else if ((temp == 6) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
			}
			else if ((temp == 7) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == 0 && i != 0 && i != c->m_height - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
			}
			else if ((temp == 8) && ((i == 0 && j != 0 && j != c->m_width - 1) || (j == c->m_width - 1 && i != 0 && i != c->m_height - 1) || (i == c->m_height - 1 && j != 0 && j != c->m_width - 1)))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
			}*/
			else if (temp == -1 && (i == 0 && j != 0 && j != c->m_width - 1))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 5;
			}
			else if (temp == -1 && (j == 0 && i != 0 && i != c->m_height - 1))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 8;
			}
			else if (temp == -1 && (j == c->m_width - 1 && i != 0 && i != c->m_height - 1))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 6;
			}
			else if (temp == -1 && (i == c->m_height - 1 && j != 0 && j != c->m_width - 1))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 7;
			}
			else if (temp == -1 && ((i == 0 && j == c->m_width - 1) || (j == 0 && i == c->m_height - 1) || (i == 0 && j == 0) || (j == c->m_width - 1 && i == c->m_height - 1) ))
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 10;
			}
			else if (temp == -1) 
			{
				worldMatrix[c->m_xCoord + WORLD_WIDTH / 2 + j][-(c->m_yCoord - WORLD_HEIGHT / 2) + i] = 0;
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