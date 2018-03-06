#include "QuadTree.h"
#include <iostream>
#include <sstream>

//## FOR USAGE EXPLENATION: See QuadTree.h ##

//##QuadTree Implementations##
QuadTree::QuadTree(QuadTreeBounds quadRect) : m_root(quadRect, 0) {}

void QuadTree::lazyInsert(std::shared_ptr<GameObject> gameObject)
{
	m_lazyInserts.push_back(gameObject);
}

int QuadTree::reconstruct()
{
	int deletions = 0;
	std::vector<std::shared_ptr<GameObject>> toReinsert;
	//Restructures tree, populating toReinsert with objects not within their proper bounds
	//and counts how many lazyDeletions have occured
	m_root.reconstruct(toReinsert, deletions);
	//Reinsert all objects that moved out of place
	for (auto it = toReinsert.begin(); it != toReinsert.end(); it++)
	{
		if (*it != nullptr)
		{
			m_root.insert(*it);
		}
	}
	//Insert all lazyInserts while we're already restructuring
	for (int i = 0; i < m_lazyInserts.size(); i++)
	{
		if (m_lazyInserts[i] != nullptr)
		{
			m_root.insert(m_lazyInserts[i]);
		}
	}
	m_lazyInserts.clear();

	return deletions;
}

QuadTreeBounds QuadTree::getBounds()
{
	return m_root.m_bounds;
}

void QuadTree::insert(std::shared_ptr<GameObject> gameObject)
{
	m_root.insert(gameObject);
}

void QuadTree::populateList(QuadTreeBounds & bounds, std::vector<std::shared_ptr<GameObject>> &gameObjects)
{
	m_root.populate(bounds, gameObjects);
}

std::set<std::shared_ptr<GameObject>> QuadTree::getAll()
{
	std::set<std::shared_ptr<GameObject>> toReturn;
	m_root.getAll(toReturn);
	return toReturn;
}

bool QuadTree::intersects(QuadTreeBounds &quadBounds1, QuadTreeBounds &quadBounds2)
{
	return !(
		quadBounds1.getX() + quadBounds1.getWidth() / 2.0f < quadBounds2.getX() - quadBounds2.getWidth() / 2.0f ||
		quadBounds1.getX() - quadBounds1.getWidth() / 2.0f > quadBounds2.getX() + quadBounds2.getWidth() / 2.0f ||
		quadBounds1.getY() - quadBounds1.getHeight() / 2.0f > quadBounds2.getY() + quadBounds2.getHeight() / 2.0f ||
		quadBounds1.getY() + quadBounds1.getWidth() / 2.0f < quadBounds2.getY() - quadBounds2.getHeight() / 2.0f
		);
}

//##QuadTreeBounds Implementations##
QuadTreeBounds::QuadTreeBounds(float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}
QuadTreeBounds::QuadTreeBounds(std::shared_ptr<GameObject> gameObject)
{
	if (gameObject != nullptr)
	{
		m_x = gameObject->getTransform()->getX();
		m_y = gameObject->getTransform()->getY();
		m_width = gameObject->getTransform()->getScale();
		m_height = gameObject->getTransform()->getScale();
	}
	else
	{
		throw "ERROR::QuadTreeBounds(std::shared_ptr<GameObject> gameObject)::GameObject given was nullptr";
	}
}

float QuadTreeBounds::getX() { return m_x; }
float QuadTreeBounds::getY() { return m_y; }
float QuadTreeBounds::getWidth() { return m_width; }
float QuadTreeBounds::getHeight() { return m_height; }


//##QuadTreeNode Implementations
QuadTree::Node::Node(QuadTreeBounds &_bounds, int pLevel) : m_bounds(_bounds), m_depth(++pLevel) {}

bool QuadTree::Node::isLeaf()
{
	return m_children[0] == nullptr;
}

void QuadTree::Node::split()
{
	//Create a child for each quadrant
	float newWidth = m_bounds.getWidth() / 2.0f;
	float newHeight = m_bounds.getHeight() / 2.0f;

	//TopLeft
	m_children[0].reset(new Node(QuadTreeBounds(m_bounds.getX() - newWidth / 2.0f, m_bounds.getY() + newHeight / 2.0f, newWidth, newHeight), m_depth));
	//TopRight
	m_children[1].reset(new Node(QuadTreeBounds(m_bounds.getX() + newWidth / 2.0f, m_bounds.getY() + newHeight / 2.0f, newWidth, newHeight), m_depth));
	//BottomLeft
	m_children[2].reset(new Node(QuadTreeBounds(m_bounds.getX() - newWidth / 2.0f, m_bounds.getY() - newHeight / 2.0f, newWidth, newHeight), m_depth));
	//BottomRight
	m_children[3].reset(new Node(QuadTreeBounds(m_bounds.getX() + newWidth / 2.0f, m_bounds.getY() - newHeight / 2.0f, newWidth, newHeight), m_depth));
	
	//Insert items into children
	for (int j = 0; j < m_items.size(); j++)
	{
		std::shared_ptr<GameObject> object = m_items[j];
		for (int i = 0; i < 4; i++)
		{
			if (object != nullptr)
			{
				m_children[i]->insert(object);
			}
		}
	}

	//Clear item collection
	m_items.clear();
}

void QuadTree::Node::populate(QuadTreeBounds& bounds, std::vector<std::shared_ptr<GameObject>> &retItems)
{
	if (!intersects(m_bounds, bounds))
	{
		return; //Not in bounds, don't perform population
	}

	if (isLeaf())
	{
		for (int i = 0; i < m_items.size(); i++)
		{
			if (m_items[i] != nullptr)
			{
				retItems.push_back(m_items[i]);
			}
			
		}
	}
	else
	{
		for (auto &child : m_children)
		{
			child->populate(bounds, retItems); //Populate from children
		}
	}
}

void QuadTree::Node::insert(std::shared_ptr<GameObject> item)
{
	if (!intersects(m_bounds, QuadTreeBounds(item)))
	{
		return; //Not in bounds, don't insert
	}

	if (isLeaf() && m_items.size() == m_maxItems && m_depth < m_maxDepth)
	{
		split(); //Too full and more depth to go, so split
	}

	if (isLeaf())
	{
		m_items.push_back(item); //Leaf node, directly add to item collection. If items is bigger than max size before split, it'll keep growing since we're at max depth
	}
	else
	{
		for (auto &child : m_children)
		{
			child->insert(item); //Attempt to insert into children
		}
	}
}

void QuadTree::Node::reconstruct(std::vector<std::shared_ptr<GameObject>> &gameObjects, int& deletions)
{
	if (isLeaf())
	{
		for (int i = 0; i < m_items.size(); i++)
		{
			if (m_items[i] != nullptr)
			{
				if (!intersects(m_bounds, QuadTreeBounds(m_items[i])))
				{
					gameObjects.push_back(m_items[i]);
					deletions++;
					m_items[i] = nullptr; //Lazy deletion. Will be removed on split, skipped on populate
				}
			}
			else {
				deletions++;
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			m_children[i]->reconstruct(gameObjects, deletions);
		}
	}
}

void QuadTree::Node::getAll(std::set<std::shared_ptr<GameObject>> &gameObjects)
{
	if (isLeaf())
	{
		for (int i = 0; i < m_items.size(); i++)
		{
			if (m_items[i] != nullptr)
			{
				gameObjects.insert(m_items[i]);
			}
		}
	}
	else 
	{
		for (int i = 0; i < 4; i++)
		{
			m_children[i]->getAll(gameObjects);
		}
	}
}

