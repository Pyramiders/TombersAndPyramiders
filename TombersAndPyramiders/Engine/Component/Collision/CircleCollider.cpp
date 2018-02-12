#include "CircleCollider.h"

CircleCollider::CircleCollider(float radius) : Collider(gameObject)
{
	m_radius = radius;
}

float CircleCollider::getRadius()
{
	return m_radius;
}

void CircleCollider::setRadius(float radius)
{
	m_radius = radius;
}
