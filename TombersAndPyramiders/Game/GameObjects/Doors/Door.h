#pragma once

#include "ComplexSprite.h"
#include "Vector2.h"

class Door : public ComplexSprite
{
public:
	enum Direction { West, East, North, South };
	enum Mode { Open = 0, Closed = 1};
	enum Animation { Opening = 2, Closing = 3 };

	Door(std::shared_ptr<ComplexSpriteInfo> spriteInfo, Vector2* colliderOffset, Direction direction, Mode mode = Closed, float startX = 0.0f, float startY = 0.0f, float scale = 1.0f);
	
	void onStart() {};
	void onUpdate(int ticks);
	void onEnd() {};

	Mode getState(); 
	void setState(Mode mode);

protected:
	virtual std::shared_ptr<ComplexSpriteInfo> createSpriteInfo(Direction direction) = 0;
	virtual Vector2* createColliderOffset(Direction direction, float scale) = 0;

private:
	Mode m_mode;
	bool m_popupActive;
};