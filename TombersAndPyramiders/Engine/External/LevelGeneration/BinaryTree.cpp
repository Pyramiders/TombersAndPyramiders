
#include "BinaryTree.h"
#include <time.h>
#include <math.h>
#include "GeneratorManager.h"

BinaryTree::BinaryTree(int width, int height)
{
	m_root = std::make_shared<BTNode>(width, height, -width/2, height/2);
}

void BinaryTree::partition(int level, int depth)
{
	m_level = level;
	m_depth = depth;
	partition(depth, m_root);
}

void BinaryTree::makeCorridors(std::vector<std::shared_ptr<Room>> rooms)
{
	makeCorridors(m_root);
	std::vector<std::shared_ptr<Corridor>> cors = GeneratorManager::getInstance()->levels[m_level]->corridors;
	fixRooms(cors, rooms);
}

void BinaryTree::fixRooms(std::vector<std::shared_ptr<Corridor>> corridors, std::vector<std::shared_ptr<Room>> rooms)
{
	for (int i = 0; i < corridors.size(); i++)
	{
		for (int j = 0; j < rooms.size(); j++)
		{
			if (corridors[i]->m_width == 3)
			{
				for (int k = 0; k < corridors[i]->m_height; k++)
				{
					if (corridors[i]->m_yCoord - k == (rooms[j]->m_yCoord - rooms[j]->m_height + 1) || corridors[i]->m_yCoord - k == (rooms[j]->m_yCoord))
					{
						//add coord set to room so door drawn there and adjacent walls become corners
						rooms[j]->doorsX.push_back(corridors[i]->m_xCoord + 1);
						rooms[j]->doorsY.push_back(corridors[i]->m_yCoord - k);
					}
				}
			}
			else
			{
				for (int k = 0; k < corridors[i]->m_width; k++)
				{
					if (corridors[i]->m_xCoord + k == (rooms[j]->m_xCoord + rooms[j]->m_width - 1) || corridors[i]->m_xCoord + k == (rooms[j]->m_xCoord))
					{
						//add coord set to room so door drawn there and adjacent walls become corners
						rooms[j]->doorsX.push_back(corridors[i]->m_xCoord + k);
						rooms[j]->doorsY.push_back(corridors[i]->m_yCoord - 1);
					}
				}
			}
		}
	}

}

void BinaryTree::makeCorridors(std::shared_ptr<BTNode> node)
{
	if (node != nullptr)
	{
		if (node->left != nullptr && node->right != nullptr)
		{
			int width = 0;
			int height = 0;
			int xCoord = 0;
			int yCoord = 0;
			if (node->left->m_boundsHeight - node->right->m_boundsHeight == 0)
			{
				//horizontal corridor
				width = node->left->m_boundsWidth / 2 + node->right->m_boundsWidth / 2;
				height = 3;
			}
			else if (node->left->m_boundsWidth - node->right->m_boundsWidth == 0)
			{
				//vertical corridor
				height = node->left->m_boundsHeight / 2 + node->right->m_boundsHeight/ 2;
				width = 3;
			}
			xCoord = node->left->m_cornerX + node->left->m_boundsWidth / 2;
			yCoord = node->left->m_cornerY - node->left->m_boundsHeight / 2;
			node->corridor = std::make_shared<Corridor>(width, height, xCoord, yCoord);
			GeneratorManager::getInstance()->levels[m_level]->corridors.push_back(node->corridor);
			makeCorridors(node->left);
			makeCorridors(node->right);
			//connect center

		}
	}
}

void BinaryTree::partition(int depth, std::shared_ptr<BTNode> node)
{
	if (depth == 0)
	{
		// make room
		//60%-80% of box
		int roomHeight = rand() % (int)ceil((0.2f * node->m_boundsHeight)) + (int)ceil((0.6f * node->m_boundsHeight));
		int roomWidth = rand() % (int)ceil((0.2f * node->m_boundsWidth)) + (int)ceil((0.6f * node->m_boundsWidth));
		int xOffset = 0;
		int yOffset = 0;
		if (node->m_boundsHeight - roomHeight != 0) 
		{
			yOffset = rand() % (node->m_boundsHeight - roomHeight);
		}
		if (node->m_boundsWidth - roomWidth != 0)
		{
			xOffset = rand() % (node->m_boundsWidth - roomWidth);
		}
		node->room = std::make_shared<Room>(roomWidth, roomHeight, node->m_cornerX + xOffset, node->m_cornerY - yOffset, false);
		GeneratorManager::getInstance()->levels[m_level]->rooms.push_back(node->room);
		return;
	}

	if (node != nullptr)
	{
		//can be improved
		int direction = 0;
		if (node->m_boundsHeight * 2 < node->m_boundsWidth)
		{
			direction = 0;
		}
		else if (node->m_boundsWidth * 2 < node->m_boundsHeight)
		{
			direction = 1;
		}
		else if (node->m_boundsHeight / 2 < 4)
		{
			direction = 0;
		} 
		else if (node->m_boundsWidth / 2 < 4)
		{
			direction = 1;
		}
		else
		{
			//choose random direction
			direction = rand() % 2;
		}

		//choose random position x for vertical, y for horizontal
		if (direction == 1)
		{ //horizontal split
			int position = rand() % (int)ceil((0.4f * node->m_boundsHeight)) + (int)ceil((0.3f * node->m_boundsHeight));
			node->left = std::make_shared<BTNode>(node->m_boundsWidth, position, node->m_cornerX, node->m_cornerY);
			node->right = std::make_shared<BTNode>(node->m_boundsWidth, node->m_boundsHeight - position, node->m_cornerX, node->m_cornerY - position);
			partition(depth - 1, node->left);
			partition(depth - 1, node->right);
		}
		else if (direction == 0)
		{ //vertical split
			int position = rand() % (int)ceil((0.4f * node->m_boundsWidth)) + (int)ceil((0.3f * node->m_boundsWidth));
			node->left = std::make_shared<BTNode>(position, node->m_boundsHeight, node->m_cornerX, node->m_cornerY);
			node->right = std::make_shared<BTNode>(node->m_boundsWidth - position, node->m_boundsHeight, node->m_cornerX + position, node->m_cornerY);
			partition(depth - 1, node->left);
			partition(depth - 1, node->right);
		}
	}
}


BinaryTree::BTNode::BTNode(int width, int height, int cornerX, int cornerY) : m_boundsWidth(width), m_boundsHeight(height), m_cornerX(cornerX), m_cornerY(cornerY)
{

}