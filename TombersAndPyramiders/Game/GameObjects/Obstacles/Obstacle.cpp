#include "Obstacle.h"
#include "ObstacleController.h"
#include "ObstaclePilot.h"
#include "DummyPilot.h"

Obstacle::Obstacle(std::shared_ptr<ComplexSpriteInfo> spriteInfo, Vector2* colliderOffset, Direction direction, Mode mode, float x, float y, float scale) : ComplexSprite(spriteInfo, x, y, 1, scale)
{
	m_mode = mode;
	changeSpriteSheet(mode);
	int temp[4] = {1000, 500, 1500, 500};
	addComponentAsParent<ObstacleController, BasePossessableController>(this, new ObstaclePilot());
	delete colliderOffset;
}

void Obstacle::onUpdate(int ticks)
{
	updateFrames(ticks);
}

Obstacle::Mode Obstacle::getState()
{
	return m_mode;
}

Vector2* Obstacle::createColliderOffset(Direction direction, float scale)
{
	Vector2* offset;
	switch(direction)
	{
	case West:
		offset = new Vector2(0.0f, 0.0f);
		break;
	case East:
		offset = new Vector2(0.0f, 0.0f);
		break;
	case North:
		offset = new Vector2(0.0f, 0.0f);
		break;
	case South:
		offset = new Vector2(0.0f, 0.0f);
		break;
	default:
		throw "ERROR::SingleDoor::createColliderOffset:: Not a valid direciton";
	}
	return offset;
}