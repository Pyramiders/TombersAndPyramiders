/*===================================================================================*//**
	BaseLongbow

	Abstract class for a base longbow.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseLongbow.h"
#include "Projectile.h"
#include "GameManager.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const float BaseLongbow::LONGBOW_PROJECTILE_COLLIDER_WIDTH = 0.5;
const float BaseLongbow::LONGBOW_PROJECTILE_COLLIDER_HEIGHT = 0.5;
const float BaseLongbow::LONGBOW_PROJECTILE_SPRITE_SCALE = 0.5;
const float BaseLongbow::LONGBOW_PROJECTILE_SPAWN_X_OFFSET_FROM_HOLDER = 1;
const float BaseLongbow::LONGBOW_PROJECTILE_SPAWN_Y_OFFSET_FROM_HOLDER = 0;
const float BaseLongbow::LONGBOW_PROJECTILE_LIFESPAN = 20;
const float BaseLongbow::LONGBOW_PROJECTILE_X_VELOCITY = 5;
const float BaseLongbow::LONGBOW_PROJECTILE_Y_VELOCITY = 0;
const float BaseLongbow::LONGBOW_ATTACK_COOLDOWN_TIME = 5;

/*----------------------------------------------------------------------------------------
	Resource Methods
----------------------------------------------------------------------------------------*/
BaseLongbow::BaseLongbow(std::string projectileImageName,
	Vector2 projectileColliderSize, Vector2 projectileSpawnOffsetFromHolder,
	float projectileSpriteScale, Vector2 projectileVelocity, float projectileLifespan) :
	BaseProjectileWeapon{ projectileImageName, projectileColliderSize, 
	projectileSpawnOffsetFromHolder, projectileSpriteScale, projectileVelocity, projectileLifespan }
{}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseLongbow::use()
{
	if (!m_isAttacking)
	{
		onStart();
	}
}

void BaseLongbow::onStart()
{
	m_isAttacking = true;
	m_timeUntilNextAttack = LONGBOW_ATTACK_COOLDOWN_TIME;
	Vector2 spawnPoint = getProjectileSpawnPoint();
	Vector2 velocity = getProjectileVelocity();
	GameManager::getInstance()->createGameObject<Projectile>(false, 
															 this, 
															 m_projectileImageName,
															 LONGBOW_PROJECTILE_COLLIDER_WIDTH, LONGBOW_PROJECTILE_COLLIDER_HEIGHT,
															 spawnPoint.getX(), spawnPoint.getY(),
															 LONGBOW_PROJECTILE_SPRITE_SCALE,
															 velocity.getX(), velocity.getY(),
															 LONGBOW_PROJECTILE_LIFESPAN);
}

void BaseLongbow::onUpdate(int ticks)
{
	updateAttack(ticks);
}

void BaseLongbow::onEnd()
{
	m_isAttacking = false;
}

void BaseLongbow::updateAttack(int ticks)
{
	if (m_isAttacking)
	{
		m_timeUntilNextAttack -= ticks / TICKS_PER_SECOND;

		if (m_timeUntilNextAttack <= 0)
		{
			onEnd();
		}
	}
}

Vector2 BaseLongbow::getProjectileSpawnPoint()
{
	Vector2 spawnPoint = Vector2(
		owner()->getTransform()->getX() + m_projectileSpawnOffsetFromHolder.getX(),
		owner()->getTransform()->getY() + m_projectileSpawnOffsetFromHolder.getY()
	);

	spawnPoint.rotateFromOrigin(
		Vector2(owner()->getTransform()->getX(), owner()->getTransform()->getY()), 
		owner()->getTransform()->getRotation()
	);

	return spawnPoint;
}

Vector2 BaseLongbow::getProjectileVelocity()
{
	Vector2 velocity = Vector2(
		m_projectileVelocity.getX(), m_projectileVelocity.getY()
	);
	
	velocity.rotate( owner()->getTransform()->getRotation() );

	return velocity;
}
