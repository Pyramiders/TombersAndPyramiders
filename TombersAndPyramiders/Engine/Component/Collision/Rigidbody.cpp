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
			std::shared_ptr<BoxCollider> blockingCollider = blockingGameObject->getComponent<BoxCollider>();

			if (!blockingCollider->isTrigger())
			{
				if (blockingGameObject != nullptr && blockingGameObject != NULL && blockingCollider != nullptr)
				{
					auto ourCollider = gameObject->getComponent<BoxCollider>();
					auto blockingTransform = blockingCollider->getGameObject()->getTransform();
					float blockingY = blockingTransform->getY() + blockingCollider->getYOffset();
					float blockingX = blockingTransform->getX() + blockingCollider->getXOffset();
					float blockingBottom = blockingY - blockingCollider->getHeight() / 2.0f;
					float blockingTop = blockingY + blockingCollider->getHeight() / 2.0f;
					float blockingLeft = blockingX - blockingCollider->getWidth() / 2.0f;
					float blockingRight = blockingX + blockingCollider->getWidth() / 2.0f;

					auto ourTransform = gameObject->getTransform();
					float ourY = ourTransform->getY() + ourCollider->getYOffset();
					float ourX = ourTransform->getX() + ourCollider->getXOffset();
					float ourTop = ourY + ourCollider->getHeight() / 2.0f;
					float ourBottom = ourY - ourCollider->getHeight() / 2.0f;
					float ourRight = ourX + ourCollider->getWidth() / 2.0f;
					float ourLeft = ourX - ourCollider->getWidth() / 2.0f;

					/*bool collidingOnBlockingsLeft = ourRight >= blockingLeft;
					bool collidingOnBlockingsRight = ourLeft <= blockingRight;
					bool collidingOnBlockingsTop = ourBottom <= blockingTop;
					bool collidingOnBlockingsBottom = ourTop >= blockingBottom;*/

					float penetrationLeft = -(ourRight - blockingLeft);
					float penetrationRight = blockingRight - ourLeft;
					float penetrationBottom = -(ourTop - blockingBottom);
					float penetrationTop = blockingTop - ourBottom;

					// Round to 1 decimal place
					/*penetrationLeft = round(penetrationLeft * 10) / 10;
					penetrationRight = round(penetrationRight * 10) / 10;
					penetrationBottom = round(penetrationBottom * 10) / 10;
					penetrationTop = round(penetrationTop * 10) / 10;*/

					std::cout << "______________________________________________" << std::endl;
					std::cout << "PenLef: " << penetrationLeft << " , PenRig: " << penetrationRight << std::endl;
					std::cout << "PenBot: " << penetrationBottom << " , PenTop: " << penetrationTop << std::endl;
					std::cout << "Velocity X: " << m_velocity.getX() << " , Velocity Y: " << m_velocity.getY() << std::endl;

					// Push left up
					/*if (m_velocity.getX() > 0 && m_velocity.getY() < 0 && abs(penetrationLeft) == abs(penetrationTop)) {
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingCollider->getX () - blockingCollider->getWidth() / 2 - m_boxCollider->getWidth() / 2 - m_boxCollider->getXOffset());
						gameObject->getTransform()->setY(blockingY + blockingCollider->getHeight() / 2 + m_boxCollider->getHeight() / 2 + m_boxCollider->getYOffset());
						std::cout << "Push left up" << std::endl;
					}
					// Push right up
					else if (m_velocity.getX() < 0 && m_velocity.getY() < 0 && abs(penetrationRight) == abs(penetrationTop)) {
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingCollider->getXOffset() + blockingCollider->getWidth() / 2 + m_boxCollider->getWidth() / 2 + m_boxCollider->getXOffset());
						gameObject->getTransform()->setY(blockingY + blockingCollider->getHeight() / 2 + m_boxCollider->getHeight() / 2 + m_boxCollider->getYOffset());
						std::cout << "Push right up" << std::endl;
					}
					// Push right down
					else if (m_velocity.getX() < 0 && m_velocity.getY() > 0 && abs(penetrationRight) == abs(penetrationBottom)) {
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingCollider->getXOffset() + blockingCollider->getWidth() / 2 + m_boxCollider->getWidth() / 2 + m_boxCollider->getXOffset());
						gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() + blockingCollider->getYOffset() - blockingCollider->getHeight() / 2 - m_boxCollider->getHeight() / 2 - m_boxCollider->getYOffset());
						std::cout << "Push right down" << std::endl;
					}
					// Push left down
					else if (m_velocity.getX() > 0 && m_velocity.getY() > 0 && abs(penetrationLeft) == abs(penetrationBottom)) {
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingCollider->getXOffset() - blockingCollider->getWidth() / 2 - m_boxCollider->getWidth() / 2 - m_boxCollider->getXOffset());
						gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() + blockingCollider->getYOffset() - blockingCollider->getHeight() / 2 - m_boxCollider->getHeight() / 2 - m_boxCollider->getYOffset());
						std::cout << "Push left down" << std::endl;
					}*/
					// Push left
					if (m_velocity.getX() > 0 && abs(penetrationLeft) < abs(penetrationRight) && abs(penetrationLeft) < abs(penetrationBottom) && abs(penetrationLeft) < abs(penetrationTop)) {
						gameObject->getTransform()->addTranslation(penetrationLeft, 0);
						//gameObject->getTransform()->setX(blockingX + blockingCollider->getXOffset() - blockingCollider->getWidth() / 2 - m_boxCollider->getWidth() / 2 - m_boxCollider->getXOffset());
						std::cout << "Push left" << std::endl;
					}
					// Push right
					else if (m_velocity.getX() < 0 && abs(penetrationRight) < abs(penetrationLeft) && abs(penetrationRight) < abs(penetrationBottom) && abs(penetrationRight) < abs(penetrationTop)) {
						gameObject->getTransform()->addTranslation(penetrationRight, 0);
						//gameObject->getTransform()->setX(blockingX + blockingCollider->getXOffset() + blockingCollider->getWidth() / 2 + m_boxCollider->getWidth() / 2 + m_boxCollider->getXOffset());
						std::cout << "Push right" << std::endl;
					}
					// Push down
					else if (m_velocity.getY() > 0 && abs(penetrationBottom) < abs(penetrationLeft) && abs(penetrationBottom) < abs(penetrationRight) && abs(penetrationBottom) < abs(penetrationTop)) {
						gameObject->getTransform()->addTranslation(0, penetrationBottom);
						//gameObject->getTransform()->setY(blockingY + blockingCollider->getYOffset() - blockingCollider->getHeight() / 2 - m_boxCollider->getHeight() / 2 - m_boxCollider->getYOffset());
						std::cout << "Push down" << std::endl;
					}
					// Push up
					else if (m_velocity.getY() < 0 && abs(penetrationTop) < abs(penetrationLeft) && abs(penetrationTop) < abs(penetrationRight) && abs(penetrationTop) < abs(penetrationBottom)) {
						gameObject->getTransform()->addTranslation(0, penetrationTop);
						//gameObject->getTransform()->setY(blockingY + blockingCollider->getYOffset() + blockingCollider->getHeight() / 2 + m_boxCollider->getHeight() / 2 + m_boxCollider->getYOffset());
						std::cout << "Push up" << std::endl;
					}

					/*
					float penetrationX = 0; //Negative if we should move left, positive if we move right
					float penetrationY = 0; //Negative if we should move down, positive if we move up

					if (collidingOnBlockingsLeft) {
						penetrationX = -(blockingCollider->getWidth() / 2.0f - (blockingX - ourRight));
						//std::cout << "from" << std::endl;
					}
					else if (collidingOnBlockingsRight) {
						penetrationX = blockingCollider->getWidth() / 2.0f - (blockingX - ourLeft);
						//std::cout << "We're hitting the wall from the right" << std::endl;
					} 
					if (collidingOnBlockingsBottom) {
						penetrationY = -(blockingCollider->getHeight() / 2.0f - (blockingY - ourTop));
						//std::cout << "We're hitting the wall from the bottom" << std::endl;
					}
					else if (collidingOnBlockingsTop){
						penetrationY = blockingCollider->getHeight() / 2.0f - (ourBottom - blockingY);
						//std::cout << "We're hitting the wall from the top" << std::endl;
					}

					std::cout << "Pen: " << penetrationX << " , " << penetrationY << std::endl;

					if (abs(penetrationX) > abs(penetrationY)) {
						gameObject->getTransform()->addTranslation(0, penetrationY);
					}
					else {
						gameObject->getTransform()->addTranslation(penetrationX, 0);
					}*/

					/*
					// Push down when try to move up
					if (m_velocity.getY() > 0 && blockingY - blockingCollider->getHeight() / 2 > ourY)
						gameObject->getTransform()->setY(blockingGameObject->getTransform()->getY() + blockingCollider->getYOffset() - blockingCollider->getHeight() / 2 - m_boxCollider->getHeight() / 2 - m_boxCollider->getYOffset());
					
					// Push up when try to move down
					else if (m_velocity.getY() < 0 && blockingY + blockingCollider->getHeight() / 2 < ourY)
						gameObject->getTransform()->setY(blockingY + blockingCollider->getHeight() / 2 + m_boxCollider->getHeight() / 2 + m_boxCollider->getYOffset());
					
					// Push left when try to move right
					else if (m_velocity.getX() > 0 && blockingX - blockingCollider->getWidth() / 2 > ourX)
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingCollider->getXOffset() - blockingCollider->getWidth() / 2 - m_boxCollider->getWidth() / 2 - m_boxCollider->getXOffset());
					
					// Push right when try to move left
					else if (m_velocity.getX() < 0 && blockingX + blockingCollider->getWidth() / 2 < ourX)
						gameObject->getTransform()->setX(blockingGameObject->getTransform()->getX() + blockingCollider->getXOffset() + blockingCollider->getWidth() / 2 + m_boxCollider->getWidth() / 2 + m_boxCollider->getXOffset());
					*/
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
