#include "Health.h"

#include "BoxCollider.h"
#include "Camera.h"
#include "Damageable.h"
#include "SpawnManager.h"

Health::Health(string spriteName, bool hasCollider) : SimpleSprite(spriteName, 0, 0, 1000)
{
	if (hasCollider)
	{
		//addComponent<BoxCollider>(this, getTransform()->getScale(), getTransform()->getScale());
		addComponent<BoxCollider>(this, 5, 5);
	}

}

Health::~Health()
{
}



void Health::onUpdate(int ticks)
{
	auto cameraXPosition = Camera::getActiveCamera()->getTransform()->getX();
	auto cameraYPosition = Camera::getActiveCamera()->getTransform()->getY();
	cameraXPosition -= 15;
	cameraYPosition += 13;

	getTransform()->setPosition(cameraXPosition, cameraYPosition);
}

	/*Damageable::setHealth()->

	if (50 < m_health <= 75) {
		
	}*/
