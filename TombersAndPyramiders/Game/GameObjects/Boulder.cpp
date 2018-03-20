#include "BoxCollider.h"
#include "BoulderController.h"
#include "Boulder.h"
#include "Rigidbody.h"

Boulder::Boulder(BasePilot* pilot) : ComplexSprite(createSpriteInfo(), 0, 0, 1.0f, 2.0f)
{
	auto boxCollider = addComponent<BoxCollider>(this, 2, 2);
	addComponent<Rigidbody>(this, boxCollider.get());
	addComponentAsParent<BoulderController, BasePossessableController>(this, pilot);
}

//Loads the boulder sprite sheet of the one rolling animation
std::shared_ptr<ComplexSpriteinfo> Boulder::createSpriteInfo()
{
	auto spriteInfo = std::make_shared<ComplexSpriteinfo>();
	spriteInfo->addInfo("boulderRolling.png", 8, 2);
	return spriteInfo;
}

void Boulder::onStart()
{
	m_lastX = getTransform()->getX();
	m_lastY = getTransform()->getY();
}

void Boulder::onUpdate(int ticks)
{
	float newX = getTransform()->getX();
	float newY = getTransform()->getY();
	float diffX = newX - m_lastX;
	float diffY = newY - m_lastY;
	float distTraveled = sqrtf(diffX * diffX + diffY * diffY) * 150.0f;

	//Update the boulders animation based on distance traveled rather than time
	updateFrames(distTraveled);

	if (diffX > 0 || diffY > 0)
	{
		Vector2 dirMoving = Vector2(diffX, diffY);
		float direction = dirMoving.getRotationInDegrees();
		getTransform()->setRotation(direction);
	}

	m_lastX = newX;
	m_lastY = newY;
}

Boulder::~Boulder()
{
}