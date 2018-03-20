#include "CircleCollider.h"

CircleCollider::CircleCollider(GameObject* gameObject, float radius) : Collider(gameObject)
{
	m_radius = radius;
	m_xOffset = 0;
	m_yOffset = 0;
}

CircleCollider::CircleCollider(GameObject* gameObject, float radius, float xPos, float yPos) : Collider(gameObject)
{
	m_radius = radius;
	m_xOffset = xPos;
	m_yOffset = yPos;
}

float CircleCollider::getRadius()
{
	return m_radius;
}

void CircleCollider::setRadius(float radius)
{
	m_radius = radius;
}