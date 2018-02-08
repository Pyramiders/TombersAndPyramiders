#include "Collider.h"
#include "Transform.h"
#include <math.h>
#include "PhysicsManager.h"

Collider::Collider(GameObject* gameObject/*, float radius*/) : Component(gameObject)/*, m_radius(radius)*/
{
	m_collision = false;
	//add to physics manager;
	PhysicsManager::getInstance()->addCollider(this);
	m_transform = gameObject->getTransform();
	m_disabled = false;
}

bool Collider::collisionDetected()
{
	return m_collision;
}

void Collider::setCollision(bool collision)
{
	m_collision = collision;
}

void Collider::setDisabled(bool value)
{
	m_disabled = value;
}

bool Collider::getDisabled()
{
	return m_disabled;
}

bool Collider::doesCollide(GameObject* other)
{
	Transform* myTrans = gameObject->getTransform();
	Transform* otherTrans = other->getTransform();

	float a = myTrans->getX() - otherTrans->getX();
	float b = myTrans->getY() - otherTrans->getY();
	float c = sqrtf(a * a + b * b);
	float myRad = myTrans->getScale() / 2.0f;
	float otherRad = otherTrans->getScale() / 2.0f;

	return c <= myRad + otherRad;
}

GameObject* Collider::getColliderObj()
{
	return m_colliderObj;
}

std::vector<GameObject*> Collider::getColliders()
{
	return m_colliders;
}

void Collider::setColliderObj(GameObject* collider)
{
	m_colliderObj = collider;
}

void Collider::clearColliders()
{
	m_colliders.clear();
}

void Collider::addCollision(GameObject* collider)
{
	m_colliders.push_back(collider);
}

//float Collider::getRadius()
//{
//	return m_radius;
//}
/*
void Collider::setRadius(float radius)
{
	m_radius = radius;
}
*/
Transform * Collider::getTransform()
{
	return m_transform;
}

Collider::~Collider()
{
	PhysicsManager::getInstance()->removeCollider(this);
}
