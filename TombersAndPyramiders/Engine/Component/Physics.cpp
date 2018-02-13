
#include "Physics.h"	

Physics::Physics(GameObject* gameObject) : Component(gameObject)
{
	m_velocity = new Vector2(0, 0);
	m_aVelocity = new Vector2(0, 0);
	m_drag = 1;
	m_snowDrag = 1;
	m_velDrag = 1;
	m_applyingForce = false;
	m_transform = gameObject->getTransform();
}

void Physics::setVelocity(Vector2* value)
{
	delete(m_velocity);
	m_velocity = value;
}

Vector2* Physics::getVelocity()
{
	return m_velocity;
}

void Physics::setAngularVelocity(Vector2* value)
{
	m_aVelocity = value;
}

Vector2* Physics::getAngularVelocity()
{
	return m_aVelocity;
}

void Physics::setApplyingForce(bool value)
{
	m_applyingForce = value;
}

bool Physics::getApplyingForce()
{
	return m_applyingForce;
}

void Physics::setSnowDrag(float value)
{
	m_snowDrag = value;
}

void Physics::addSnowDrag(float value)
{
	m_snowDrag += value;
}

float Physics::getSnowDrag()
{
	return m_snowDrag;
}

void Physics::setDrag(float value)
{
	m_drag = value;
}

void Physics::addDrag(float value)
{
	m_drag += value;
}

void Physics::setVelDrag(float value)
{
	m_velDrag = value;
}

float Physics::getVelDrag()
{
	return m_velDrag;
}

void Physics::addVelDrag(float value)
{
	m_velDrag += value;
}

float Physics::getDrag()
{
	return m_drag;
}

void Physics::onUpdate(int ticks)
{
	//if (!_applyingForce) {
	m_velocity->setX(m_velocity->getX() * m_velDrag);
	m_velocity->setY(m_velocity->getY() * m_velDrag);
	//}
	m_transform->addX(m_velocity->getX() * m_drag * m_snowDrag * ((float)ticks) / 1000);
	m_transform->addY(m_velocity->getY() * m_drag * m_snowDrag * ((float)ticks) / 1000);
	//setup angular velocity

}

Physics::~Physics()
{
	if (m_velocity != NULL)
		delete(m_velocity);
	if (m_aVelocity != NULL)
		delete(m_aVelocity);
}