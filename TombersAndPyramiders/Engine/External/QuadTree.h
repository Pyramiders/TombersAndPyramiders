#pragma once

/*
	##CLASSES##

	QuadTree	
		- Constructed with a QuadTreeBounds which represents the total bounds of the world
		- Used for fast culling of GameObjects

	QuadTreeBounds:
		- Represents the x/y/width/height boundaries of QuadTrees
		- Can be constructed with GameObject's or raw x/y/width/height

	##PUBLIC METHODS##

	QuadTree
		QuadTree(QuadTreeBounds quadRect)
		void insert(std::shared_ptr<GameObject> gameObject)
		void lazyInsert(std::shared_ptr<GameObject> gameObject)
		void populateList(QuadTreeBounds & bounds, std::vector<std::shared_ptr<GameObject>> &gameObjects)
		int reconstruct()
		QuadTreeBounds getBounds()
		std::set<std::shared_ptr<GameObject>> getAll()
*/

#include <vector>
#include <memory>
#include "GameObject.h"
#include <set>

//QuadTree Boundaries used for representing x/y/width/height collision boundaries
struct QuadTreeBounds
{
private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
public:
	QuadTreeBounds(float x, float y, float width, float height);
	QuadTreeBounds(std::shared_ptr<GameObject> gameObject);
	float getX();
	float getY();
	float getWidth();
	float getHeight();
};

//QuadTree implementation used for culling
class QuadTree
{
private:
	//Maximum number of Items a node can hold until splitting
	static const int m_maxItems = 10;
	//Maximum depth of the quadTree
	static const int m_maxDepth = 4; 

	//Bounding box intersection
	static bool intersects(QuadTreeBounds &quadBounds1, QuadTreeBounds &quadBounds2);

	//Node constituting tree structure
	struct Node
	{
	public:
		QuadTreeBounds m_bounds; //physical bounds of node
		const int m_depth; //depth

		std::unique_ptr<Node> m_children[4]; //child nodes
		std::vector<std::shared_ptr<GameObject>> m_items; //collection of retItems

		Node(QuadTreeBounds &_bounds, int pLevel);

		bool isLeaf();
		void split();
		void populate(QuadTreeBounds& bounds, std::vector<std::shared_ptr<GameObject>> &retItems);
		void insert(std::shared_ptr<GameObject> item);
		void reconstruct(std::vector<std::shared_ptr<GameObject>> &gameObjects, int& deletions);
		void getAll(std::set<std::shared_ptr<GameObject>> &gameObjects);
	};

	Node m_root;

	//Objects to insert lazily on next tree reconstructions
	std::vector<std::shared_ptr<GameObject>> m_lazyInserts;

public:
	QuadTree(QuadTreeBounds quadRect);
	//Immediate insertion into QuadTree
	void insert(std::shared_ptr<GameObject> gameObject);
	//Delayed insertions to be invoked on reconstruction
	void lazyInsert(std::shared_ptr<GameObject> gameObject);
	//Given the QuadTreeBounds, populates the gameObjects vector with all game objects within the bounds
	void populateList(QuadTreeBounds & bounds, std::vector<std::shared_ptr<GameObject>> &gameObjects);
	//Reorganizes the tree, updating moved objects and handling lazy deletion/lazy insertion
	int reconstruct();
	//Returns the QuadTreeBounds of the root node
	QuadTreeBounds getBounds();
	//Returns all of the gameObjects found within the QuadTree
	std::set<std::shared_ptr<GameObject>> getAll();
};