#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* parentGameObject, float width, float height) : Collider(parentGameObject)
{
	m_width = width;
	m_height = height;
}

float BoxCollider::getWidth()
{
	return m_width;
}

float BoxCollider::getHeight()
{
	return m_height;
}

void BoxCollider::setWidth(float width)
{
	m_width = width;
}

void BoxCollider::setHeight(float height)
{
	m_height = height;
}