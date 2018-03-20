#include "BoulderController.h"
#include "Rigidbody.h"
#include "SharedConstants.h"
#include "GameManager.h"
#include "DamagingRegion.h"

const float BoulderController::MAX_MOVESPEED = 0.8f;
const float BoulderController::FRICTION = 0.95f;
const float BoulderController::COOLDOWN = 3000.0f;

BoulderController::BoulderController(GameObject* parentGameobject, BasePilot* pilot) : BasePossessableController(parentGameobject, pilot) {
	m_cooldownTicker = 0.0f;
}

//Lazy-load rigidBody on possession and set our friction
void BoulderController::onPossessionStart()
{
	m_rigidBody = gameObject->getComponent<Rigidbody>();
	if (m_rigidBody != nullptr)
	{
		m_rigidBody->setFrictionCoefficient(FRICTION);
	}
}

void BoulderController::onPossessionEnd()
{
	m_rigidBody = nullptr;
}

//On movement, update rigid body, update the Boulders cooldown, and update the damagingRegion is the Boulder is in attack mode
void BoulderController::move(Vector2 direction)
{
	if (m_rigidBody != nullptr && direction.getMagnitude() > 0)
	{
		direction.normalize();
		if (m_rigidBody->getVelocity().getMagnitude() < MAX_MOVESPEED)
		{
			Vector2 velocity = Vector2(direction.getX() / 200.0f, direction.getY() / 200.0f);
			m_rigidBody->addVelocity(velocity);
		}
	}
	m_cooldownTicker -= FRAME_RATE;

	if (m_damagingRegion != nullptr)
	{
		if (COOLDOWN - m_cooldownTicker >= 1000)
		{
			destroy(m_damagingRegion->getId());
			m_damagingRegion = nullptr;
		}
		else
		{
			//Where infront from non-rotation object
			Vector2 dirMoving = Vector2(m_rigidBody->getVelocity().getX(), m_rigidBody->getVelocity().getY());
			dirMoving.normalize();
			Vector2 newPosition = Vector2(gameObject->getTransform()->getX() + dirMoving.getX(), gameObject->getTransform()->getY() + dirMoving.getY());
			m_damagingRegion->getTransform()->setPosition(newPosition.getX(), newPosition.getY());
		}
	}
}

//If the boulder isn't on cooldown, go into attack mode, launching it in the direction it's traveling, creating an invisible damaging region is none exists
void BoulderController::trigger()
{
	if (m_cooldownTicker <= 0.0f && m_rigidBody != nullptr)
	{
		m_rigidBody->addVelocity(m_rigidBody->getVelocity());
		m_rigidBody->addVelocity(m_rigidBody->getVelocity());
		m_rigidBody->addVelocity(m_rigidBody->getVelocity());
		m_cooldownTicker = COOLDOWN;
		if (m_damagingRegion == nullptr)
		{
			auto collider = gameObject->getComponent<BoxCollider>();
			m_damagingRegion = GameManager::getInstance()->createGameObject<DamagingRegion>(false, 20, "IceTile.png", collider->getWidth(), collider->getHeight(), false, 0, 0, 0.0f);
		}
	}
}