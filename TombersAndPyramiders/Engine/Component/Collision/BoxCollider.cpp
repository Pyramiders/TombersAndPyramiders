 #include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* parentGameObject, float width, float height) : Collider(parentGameObject)
{
	m_width = width;
	m_height = height;
	m_xOffset = 0;
	m_yOffset = 0;
}

BoxCollider::BoxCollider(GameObject* parentGameObject, float width, float height, float xPos, float yPos) : Collider(parentGameObject)
{
	m_width = width;
	m_height = height;
	m_xOffset = xPos;
	m_yOffset = yPos;
}

float BoxCollider::getWidth()
{
	return m_width * gameObject->getTransform()->getScale();
}

float BoxCollider::getHeight()
{
	return m_height * gameObject->getTransform()->getScale();
}

void BoxCollider::setWidth(float width)
{
	m_width = width;
}

void BoxCollider::setHeight(float height)
{
	m_height = height;
}