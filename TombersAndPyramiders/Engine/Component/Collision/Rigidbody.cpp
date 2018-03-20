#include "Rigidbody.h"

Rigidbody::Rigidbody(GameObject* gameObject, BoxCollider* collider) : Component(gameObject)
{
	m_boxCollider = collider;
	m_frictionCoefficient = 1.0f;
}

void Rigidbody::BlockMovement()
{
	if (m_boxCollider && m_boxCollider->collisionDetected())
	{
		for (int i = 0; i < m_boxCollider->getColliders().size(); ++i)
		{
			GameObject* blockingGameObject = m_boxCollider->getColliders()[i];
			if (blockingGameObject == nullptr || blockingGameObject == NULL) {
				//throw "RIGIDBODY::BLOCKMOVEMENT::NULL PTR FIX ME PLZ GUYS"; //TODO:: Michael & Evgeni:: Doesent get hit, blockingGameObject has garbage data and is not nullptr. getComponent crashes after this check fails
				continue;
			}
			std::shared_ptr<BoxCollider> collider = blockingGameObject->getComponent<BoxCollider>();
			if (!collider->isTrigger())
			{
				if (blockingGameObject != nullptr && blockingGameObject != NULL && blockingGameObject->hasComponent<BoxCollider>())
				{
					// Push down when try to move up
					if (m_velocity.getY() > 0 && blockingGameObject->getTransform()->getY() + blockingGameObject->getComponent<BoxCollider>()->getYOffset() - blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 > gameObject->getTransform()->getY() + gameObject->getComponent<BoxCollider>()->getYOffset())
						gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() + blockingGameObject->getComponent<BoxCollider>()->getYOffset() - blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 - m_boxCollider->getHeight() / 2 - m_boxCollider->getYOffset());
					// Push up when try to move down
					else if (m_velocity.getY() < 0 && blockingGameObject->getTransform()->getY() + blockingGameObject->getComponent<BoxCollider>()->getYOffset() + blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 < gameObject->getTransform()->getY() + gameObject->getComponent<BoxCollider>()->getYOffset())
						gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() + blockingGameObject->getComponent<BoxCollider>()->getYOffset() + blockingGameObject->getComponent<BoxCollider>()->getHeight() / 2 + m_boxCollider->getHeight() / 2 + m_boxCollider->getYOffset());
					// Push left when try to move right
					if (m_velocity.getX() > 0 && blockingGameObject->getTransform()->getX() + blockingGameObject->getComponent<BoxCollider>()->getXOffset() - blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 > gameObject->getTransform()->getX() + gameObject->getComponent<BoxCollider>()->getXOffset())
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingGameObject->getComponent<BoxCollider>()->getXOffset() - blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 - m_boxCollider->getWidth() / 2 - m_boxCollider->getXOffset());
					// Push right when try to move left
					else if (m_velocity.getX() < 0 && blockingGameObject->getTransform()->getX() + blockingGameObject->getComponent<BoxCollider>()->getXOffset() + blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 < gameObject->getTransform()->getX() + gameObject->getComponent<BoxCollider>()->getXOffset())
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingGameObject->getComponent<BoxCollider>()->getXOffset() + blockingGameObject->getComponent<BoxCollider>()->getWidth() / 2 + m_boxCollider->getWidth() / 2 + m_boxCollider->getXOffset());
				}
			}
		}
	}
}

void Rigidbody::setVelocity(Vector2 v)
{
	m_velocity = v;
}

Vector2 Rigidbody::getVelocity()
{
	return m_velocity;
}

void Rigidbody::setFrictionCoefficient(float friction)
{
	m_frictionCoefficient = friction;
}

void Rigidbody::addVelocity(Vector2 v)
{
	m_velocity.setX(m_velocity.getX() + v.getX());
	m_velocity.setY(m_velocity.getY() + v.getY());
}

void Rigidbody::onUpdate(int ticks)
{
	BlockMovement();
	gameObject->getTransform()->addTranslation(m_velocity.getX(), m_velocity.getY());

	m_velocity.setX(m_velocity.getX() * m_frictionCoefficient);
	m_velocity.setY(m_velocity.getY() * m_frictionCoefficient);
	if (m_velocity.getMagnitude() < 0.001f)
	{
		m_velocity.setX(0);
		m_velocity.setY(0);
	}
}
