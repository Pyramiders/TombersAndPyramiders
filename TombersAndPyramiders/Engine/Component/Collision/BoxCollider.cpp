#include "BoxCollider.h"

BoxCollider::BoxCollider(GameObject* parentGameObject, float width, float height) : Collider(parentGameObject)
{
	m_width = width;
	m_height = height;
	updateCorners();
}

float BoxCollider::getWidth()
{
	return m_width;
}

float BoxCollider::getHeight()
{
	return m_height;
}

Vector2* BoxCollider::getCorner(int index)
{
	return m_corners[index];
}

void BoxCollider::setWidth(float width)
{
	m_width = width;
}

void BoxCollider::setHeight(float height)
{
	m_height = height;
}

void BoxCollider::updateCorners()
{
	Vector2 origin(getTransform()->getX(),getTransform()->getY()); // The centre point of the box

	//Top Left corner
	m_corners[0]->setX(getTransform()->getX() - m_width / 2);
	m_corners[0]->setY(getTransform()->getY() + m_height / 2);
	m_corners[0]->rotateFromOrigin(origin, getTransform()->getRotation());
	//Top Right corner
	m_corners[1]->setX(getTransform()->getX() + m_width / 2);
	m_corners[1]->setY(getTransform()->getY() + m_height / 2);
	m_corners[1]->rotateFromOrigin(origin, getTransform()->getRotation());
	//Bottom Right corner
	m_corners[2]->setX(getTransform()->getX() + m_width / 2);
	m_corners[2]->setY(getTransform()->getY() - m_height / 2);
	m_corners[2]->rotateFromOrigin(origin, getTransform()->getRotation());
	//Bottom Left corner
	m_corners[3]->setX(getTransform()->getX() - m_width / 2);
	m_corners[3]->setY(getTransform()->getY() - m_height / 2);
	m_corners[3]->rotateFromOrigin(origin, getTransform()->getRotation());
}