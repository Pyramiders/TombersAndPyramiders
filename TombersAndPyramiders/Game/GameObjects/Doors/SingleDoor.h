#pragma once

#include "Door.h"

class SingleDoor : public Door
{
public:
	SingleDoor(Direction direction, Mode mode = Closed, float startX = 0.0f, float startY = 0.0f, float scale = 1.0f);
	
protected:
	std::shared_ptr<ComplexSpriteInfo> createSpriteInfo(Direction direction);
	Vector2* createColliderOffset(Direction direction, float scale);
};