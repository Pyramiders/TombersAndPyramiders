#pragma once

#include <memory>
#include "Room.h"
#include <vector>
#include "Doorway.h"
#include "Corridor.h"

class BinaryTree {

public:
	int m_depth;
	int m_level;
	BinaryTree(int width, int height);
	void partition(int level, int depth);
	void makeRooms();
	void makeCorridors(std::vector<std::shared_ptr<Room>> rooms);
private:
	struct BTNode {
	public:

		int m_cornerY;
		int m_cornerX;
		int m_boundsWidth;
		int m_boundsHeight;
		int m_width;
		int m_height;

		std::shared_ptr<BTNode> left;
		std::shared_ptr<BTNode> right;
		std::shared_ptr<Room> room;
		std::shared_ptr<Corridor> corridor;
		std::vector<std::shared_ptr<Doorway>> doorways;

		BTNode(int width, int height, int cornerX, int cornerY);
		

	};

	void partition(int depth, std::shared_ptr<BTNode> node);
	void fixRooms(std::vector<std::shared_ptr<Corridor>> corridors, std::vector<std::shared_ptr<Room>> rooms);
	void makeCorridors(std::shared_ptr<BTNode> node);
	std::shared_ptr<BTNode> m_root;

};