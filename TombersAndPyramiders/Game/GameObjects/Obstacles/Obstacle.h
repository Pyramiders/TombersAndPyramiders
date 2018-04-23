#pragma once

#include "ComplexSprite.h"
#include "Vector2.h"

class Obstacle : public ComplexSprite
{
public:
	enum Direction { East = 0, South = 1, West = 2, North = 3 }; //in same rotation direction as getRotation for transforms.
	enum Mode { Enabled = 0, Disabled = 1};


	Obstacle(std::shared_ptr<ComplexSpriteInfo> spriteInfo, Vector2* colliderOffset, Direction direction, Mode mode = Enabled, float startX = 0.0f, float startY = 0.0f, float scale = 1.0f);
	
	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

	Mode getState(); 
	virtual void setState(Mode mode) = 0;

protected:
	std::shared_ptr<ComplexSpriteInfo> createSpriteInfo(Direction direction) {};
	Vector2* createColliderOffset(Direction direction, float scale);
	Mode m_mode;

private:
};