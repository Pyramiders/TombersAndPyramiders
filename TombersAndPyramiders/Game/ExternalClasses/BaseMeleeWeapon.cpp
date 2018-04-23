/*===================================================================================*//**
	BaseMeleeWeapon

	Abstract class for a base melee weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseMeleeWeapon.h"
#include "DamagingRegion.h"
#include "Inventory.h"
#include "GameManager.h"
#include "BoxCollider.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseMeleeWeapon::BaseMeleeWeapon(int damage, string imageName, float colliderWidth, float colliderHeight, 
	bool destroyOnCollision, float criticalHitChance, float attackCooldownTime, 
	float xOffsetFromHolder, float yOffsetFromHolder, float colliderScale) :
	BaseWeapon(damage, criticalHitChance, attackCooldownTime)
{
	m_offsetFromHolder = Vector2(xOffsetFromHolder, yOffsetFromHolder);
	m_damagingRegion = GameManager::getInstance()->createGameObject<DamagingRegion>(false, damage, imageName, 
		colliderWidth, colliderHeight, criticalHitChance, destroyOnCollision, 0, 0, colliderScale);
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseMeleeWeapon::setOwnerId(int id)
{
	m_damagingRegion->setOwnerId(id);
}

bool BaseMeleeWeapon::use()
{
	auto willAttack = !m_isAttacking;

	if (willAttack)
	{
		onStart();
	}

	return willAttack;
}

void BaseMeleeWeapon::onStart()
{
	m_isAttacking = true;
	m_timeUntilNextAttack = m_attackCooldownTime;
	m_damagingRegion->clearHitList();
	m_damagingRegion->getTransform()->setScale(1);
	m_damagingRegion->getComponent<BoxCollider>()->setDisabled(false);
}

void BaseMeleeWeapon::onUpdate(int ticks)
{
	updatePosition();
	updateAttack(ticks);
}

void BaseMeleeWeapon::onEnd()
{
	m_isAttacking = false;
	m_damagingRegion->getTransform()->setScale(0);
	m_damagingRegion->getComponent<BoxCollider>()->setDisabled(true);
}

void BaseMeleeWeapon::updatePosition()
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

		/* Set the weapon's position and rotation about its center. */
		m_damagingRegion->getTransform()->setPosition(newPosition.getX(), newPosition.getY());
		m_damagingRegion->getTransform()->setRotation(owner()->getTransform()->getRotation());
	}
}

void BaseMeleeWeapon::updateAttack(int ticks)
{
	if (m_isAttacking)
	{
		m_timeUntilNextAttack -= (float) ticks / 1000.0f;

		if (m_timeUntilNextAttack <= 0)
		{
			onEnd();
		}
	}
}
