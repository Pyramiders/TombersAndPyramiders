/*===================================================================================*//**
	BaseProjectileWeapon

	Abstract class for a base projectile weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseProjectileWeapon.h"
#include "Projectile.h"
#include "GameManager.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseProjectileWeapon::BaseProjectileWeapon(int damage, std::string projectileImageName,
	Vector2 projectileColliderSize, bool destroyProjectilesOnCollision, float criticalHitChance, 
	float attackCooldownTime, 
	Vector2 projectileSpawnOffsetFromHolder,
	float projectileSpriteScale, Vector2 projectileVelocity, float projectileLifespan) :
	BaseWeapon(damage, criticalHitChance, attackCooldownTime),
	m_projectileImageName{ projectileImageName }, 
	m_projectileColliderSize{ projectileColliderSize }, 
	m_destroyProjectilesOnCollision{ destroyProjectilesOnCollision }, 
	m_projectileSpawnOffsetFromHolder{ projectileSpawnOffsetFromHolder }, 
	m_projectileSpriteScale{ projectileSpriteScale }, 
	m_projectileVelocity{ projectileVelocity }, 
	m_projectileLifespan{ projectileLifespan }
{}


/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseProjectileWeapon::setOwnerId(int id)
{}

bool BaseProjectileWeapon::use()
{
	auto willAttack = !m_isAttacking;

	if (willAttack)
	{
		onStart();
	}

	return willAttack;
}

void BaseProjectileWeapon::onStart()
{
	m_isAttacking = true;
	m_timeUntilNextAttack = m_attackCooldownTime;
	Vector2 spawnPoint = getProjectileSpawnPoint();
	Vector2 velocity = getProjectileVelocity();
	std::shared_ptr<Projectile> newProjectile =
		GameManager::getInstance()->createGameObject<Projectile>(
			false,
			m_damage,
			m_projectileImageName,
			m_projectileColliderSize.getX(), m_projectileColliderSize.getY(),
			m_criticalHitChance, 
			m_destroyProjectilesOnCollision,
			spawnPoint.getX(), spawnPoint.getY(),
			-owner()->getTransform()->getRotation(), 
			m_projectileSpriteScale,
			velocity.getX(), velocity.getY(),
			m_projectileLifespan);

	newProjectile->setOwnerId(owner()->getId());
}

void BaseProjectileWeapon::onUpdate(int ticks)
{
	updateAttack(ticks);
}

void BaseProjectileWeapon::onEnd()
{
	m_isAttacking = false;
}

void BaseProjectileWeapon::updateAttack(int ticks)
{
	if (m_isAttacking)
	{
		m_timeUntilNextAttack -= (float)ticks / 1000.0f;

		if (m_timeUntilNextAttack <= 0)
		{
			onEnd();
		}
	}
}

Vector2 BaseProjectileWeapon::getProjectileSpawnPoint()
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

Vector2 BaseProjectileWeapon::getProjectileVelocity()
{
	Vector2 velocity = Vector2(
		m_projectileVelocity.getX(), m_projectileVelocity.getY()
	);

	velocity.rotate(owner()->getTransform()->getRotation());

	return velocity;
}
