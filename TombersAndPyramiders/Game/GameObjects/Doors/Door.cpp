#include "Door.h"
#include "DoorController.h"
#include "DummyPilot.h"

Door::Door(std::shared_ptr<ComplexSpriteinfo> spriteInfo, Vector2* colliderOffset, Direction direction, Mode mode, float x, float y, float scale) : ComplexSprite(spriteInfo, x, y)
{
	getTransform()->setScale(scale);
	m_mode = mode;
	changeSprite(mode);
	addComponentAsParent<DoorController, BasePossessableController>(this, new DummyPilot());
	addComponent<BoxCollider>(this, colliderOffset->getX(), colliderOffset->getY()); //Offset of colliderOffset->getX(), colliderOffset->getY() when offset added
	delete colliderOffset;
}

void Door::onUpdate(int ticks)
{
	updateFrames(ticks);
}

void Door::setState(Mode mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	case Door::Open:
		changeSprite(Open);
		getComponent<BoxCollider>()->setDisabled(true);
		break;
	case Door::Closed:
		changeSprite(Closed);
		getComponent<BoxCollider>()->setDisabled(false);
		break;
	default:
		break;
	}
}

Door::Mode Door::getState()
{
	return m_mode;
}