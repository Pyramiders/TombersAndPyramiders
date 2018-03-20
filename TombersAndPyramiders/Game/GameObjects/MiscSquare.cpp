#include "MiscSquare.h"
#include "BoxCollider.h"

MiscSquare::MiscSquare(string spriteName, bool hasCollider, float colliderSize_x, float colliderSize_y) : SimpleSprite(spriteName, 0, 0)
{
	if (hasCollider)
	{
		addComponent<BoxCollider>(this, colliderSize_x, colliderSize_y);
	}
}

MiscSquare::~MiscSquare()
{
}