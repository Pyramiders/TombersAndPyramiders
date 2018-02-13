#include "Rigidbody.h"

Rigidbody::Rigidbody(GameObject* gameObject, BoxCollider* collider) : Component(gameObject)
{
	m_boxCollider = collider;
}

void Rigidbody::BlockMovement()
{
	if (m_boxCollider && m_boxCollider->collisionDetected())
	{
		for (int i = 0; i < m_boxCollider->getColliders().size(); ++i)
		{
			GameObject* blockingGameObject = m_boxCollider->getColliders()[i];
			if (blockingGameObject != nullptr && blockingGameObject != NULL && blockingGameObject->hasComponent<BoxCollider>())
			{
				// Push down when try to move up
				if (m_velocity.getY() > 0 && blockingGameObject->getTransform()->getY() - blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 > gameObject->getTransform()->getY())
					gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() - blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 - m_boxCollider->getHeight() / 2);
				// Push up when try to move down
				else if (m_velocity.getY() < 0 && blockingGameObject->getTransform()->getY() + blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 < gameObject->getTransform()->getY())
					gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() + blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 + m_boxCollider->getHeight() / 2);
				// Push left when try to move right
				if (m_velocity.getX() > 0 && blockingGameObject->getTransform()->getX() - blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 > gameObject->getTransform()->getX())
					gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() - blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 - m_boxCollider->getWidth() / 2);
				// Push right when try to move left
				else if (m_velocity.getX() < 0 && blockingGameObject->getTransform()->getX() + blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 < gameObject->getTransform()->getX())
					gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 + m_boxCollider->getWidth() / 2);
			}
		}
	}
}

void Rigidbody::setVelocity(Vector2 v)
{
	m_velocity = v;
}

void Rigidbody::onUpdate(int ticks)
{
	BlockMovement();
}
