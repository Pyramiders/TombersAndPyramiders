/*===================================================================================*//**
	BaseShield
	
	Abstract class for a base shield.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseShield.h"
#include "Inventory.h"
#include "GameManager.h"

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
BaseShield::BaseShield(string imageName, float damageMultiplier, float cooldownTime) :
	m_damageMultiplier{  }, 
	m_blockCooldownTime{ 0.5f },
	m_isBlocking{ false },
	m_offsetFromHolder{ Vector2(1, 0) }
{
	m_sprite = GameManager::getInstance()->createGameObject<SimpleSprite>(false, imageName, 0, 0, 0, 0);
}

std::shared_ptr<BaseItem> BaseShield::addSubclassToInventory()
{
	return m_inventory->setShield(shared_from_this());
}

bool BaseShield::use()
{
	auto willBlock = !m_isBlocking;

	if (willBlock)
	{
		onStart();
	}

	return willBlock;
}

void BaseShield::onStart()
{
	m_isBlocking = true;
	m_timeUntilNextBlock = m_blockCooldownTime;
	m_sprite->getTransform()->setScale(1);
}

void BaseShield::onUpdate(int ticks)
{
	updatePosition();
	updateBlock(ticks);
}

void BaseShield::onEnd()
{
	m_isBlocking = false;
	m_sprite->getTransform()->setScale(0);
}

bool BaseShield::isBlocking()
{
	return m_isBlocking;
}

int BaseShield::calculateRealDamage(int damage)
{
	return (int)((float)damage * m_damageMultiplier);
}

void BaseShield::updatePosition()
{
	if (owner() != nullptr)
	{
		/* Get the coordinates of the weapon before rotation. */
		float newX = owner()->getTransform()->getX() + m_offsetFromHolder.getX();
		float newY = owner()->getTransform()->getY() + m_offsetFromHolder.getY();

		/* Rotate the position about the weapon holder. */
		Vector2 newPosition = Vector2(newX, newY);
		newPosition.rotateFromOrigin(
			Vector2(owner()->getTransform()->getX(), owner()->getTransform()->getY()),
			owner()->getTransform()->getRotation()
		);

		m_sprite->getTransform()->setPosition(newPosition.getX(), newPosition.getY());

		/* Set the shield's rotation about its center. */
		m_sprite->getTransform()->setRotation(-owner()->getTransform()->getRotation());
	}
}

void BaseShield::updateBlock(int ticks)
{
	if (m_isBlocking)
	{
		m_timeUntilNextBlock -= (float)ticks / 1000.0f;

		if (m_timeUntilNextBlock <= 0)
		{
			onEnd();
		}
	}
}
