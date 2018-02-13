
#include "PhysicsManager.h"
#include <stdio.h>
#include <cmath>
#include "SceneManager.h"
#include <algorithm>
#include "Vector2.h"
#include "Scene.h"

PhysicsManager* PhysicsManager::s_instance;

PhysicsManager* PhysicsManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new PhysicsManager();
	return s_instance;
}

void PhysicsManager::onStart()
{
	//load gameobjects in scene into vector list
	m_sceneObjects = SceneManager::getInstance()->getCurrentScene()->sceneObjects;
}

void PhysicsManager::onUpdate(int ticks)
{
	//TODO: change to iterators by beta or release
	if (m_sceneColliders.size() > 1)
	{
		for (int i = 0; i < m_sceneColliders.size(); i++)
		{
			m_sceneColliders[i]->clearColliders();
			m_sceneColliders[i]->setCollision(false);
		}
		for (int i = 0; i < m_sceneColliders.size() - 1; i++)
		{
			for (int j = i + 1; j < m_sceneColliders.size(); j++)
			{
				Collider* c1 = m_sceneColliders[i];
				Collider* c2 = m_sceneColliders[j];
				if (!c1->getDisabled() && !c2->getDisabled())
				{
					if (checkCollision(c1, c2))
					{
						c1->addCollision(c2->getGameObject());
						c1->setCollision(true);
						c2->setCollision(true);
						c2->addCollision(c1->getGameObject());
					}
				}
			}
		}
	}
}

void PhysicsManager::addCollider(Collider* c)
{
	m_sceneColliders.push_back(c);
}

void PhysicsManager::removeCollider(Collider* c)
{
	m_sceneColliders.erase(std::remove(m_sceneColliders.begin(), m_sceneColliders.end(), c), m_sceneColliders.end());
}

void PhysicsManager::onEnd()
{

}

bool PhysicsManager::checkCollision(Collider* c1, Collider* c2)
{
	// Determine the type of collision (i.e. circle->circle, circle->box, box->box)
	CircleCollider *circleCollider1 = dynamic_cast<CircleCollider*>(c1);
	CircleCollider *circleCollider2 = dynamic_cast<CircleCollider*>(c2);
	BoxCollider *boxCollider1 = dynamic_cast<BoxCollider*>(c1);
	BoxCollider *boxCollider2 = dynamic_cast<BoxCollider*>(c2);

	if (circleCollider1 != NULL && circleCollider2 != NULL) // Circle on Circle Collision
	{
		return checkCircleCollision(circleCollider1, circleCollider2);
	}

	else if (boxCollider1 != NULL & boxCollider2 != NULL) // Box on Box Collision
	{
		return checkBoxCollision(boxCollider1, boxCollider2);
	}
	else if (circleCollider1 != NULL && boxCollider2 != NULL) // Circle on Box Collision
	{
		return checkCircleBoxCollision(circleCollider1, boxCollider2);
	}
	else if (circleCollider2 != NULL && boxCollider1 != NULL) // Box on Circle Collision
	{
		return checkCircleBoxCollision(circleCollider2, boxCollider1);
	}
	return false; // We can't determine if there was a collision
}

bool PhysicsManager::checkCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	Transform* c1transform = c1->getGameObject()->getTransform();
	Transform* c2transform = c2->getGameObject()->getTransform();
	float radiusDistance = sqrt(pow(c1transform->getX() - c2transform->getX(), 2) + pow(c1transform->getY() - c2transform->getY(), 2));

	return radiusDistance < (c1->getRadius() - 0.2f + c2->getRadius());
}

bool PhysicsManager::checkBoxCollision(BoxCollider* c1, BoxCollider* c2)
{
	Transform* c1transform = c1->getGameObject()->getTransform();
	Transform* c2transform = c2->getGameObject()->getTransform();
	return !(c1transform->getX() + c1->getWidth() / 2 < c2transform->getX() - c2->getWidth() / 2
		|| c1transform->getX() - c1->getWidth() / 2 > c2transform->getX() + c2->getWidth() / 2
		|| c1transform->getY() - c1->getHeight() / 2 > c2transform->getY() + c2->getHeight() / 2
		|| c1transform->getY() + c1->getHeight() / 2 < c2transform->getY() - c2->getHeight() / 2);
}

bool PhysicsManager::checkCircleBoxCollision(CircleCollider* c, BoxCollider* b)
{
	Transform* ctransform = c->getGameObject()->getTransform();
	Transform* btransform = b->getGameObject()->getTransform();
	float distanceX = abs(ctransform->getX() - btransform->getX());
	float distanceY = abs(ctransform->getY() - btransform->getY());

	if (distanceX > b->getWidth() / 2 + c->getRadius()
		|| distanceY > b->getHeight() / 2 + c->getRadius())
		return false;

	if (distanceX <= b->getWidth() / 2
		|| distanceY <= b->getHeight())
		return true;

	return (pow(distanceX - b->getWidth() / 2,2) + pow(distanceY - b->getHeight() / 2,2) <= pow(c->getRadius(),2));
}

void PhysicsManager::purge()
{
	m_sceneColliders.clear();
}
