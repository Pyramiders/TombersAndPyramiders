#include "Wall.h"
#include "InputManager.h"
#include "SpriteRenderer.h"

/*
Constructor called when the GameObject is created. Any GameObject specific creation code can go here.
This includes adding relevant components or any setup.

By default, GameObject's base class has a Transform component
*/
Wall::Wall() : SimpleSprite("WallLarge.png", 0, 0)
{
	m_boxCollider = addComponent<BoxCollider>(this, 10, 10);
}

Wall::~Wall()
{
}

void Wall::onUpdate(int ticks)
{
}