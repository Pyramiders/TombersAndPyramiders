/*===================================================================================*//**
	Projectile
	
	A DamagingRegion that is fired by a projectile weapon, moves, and destroys itself 
	after a set duration or after hitting something.
    
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <memory>
#include "Projectile.h"
#include "BaseItem.h"
#include "CharacterController.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Projectile::Projectile(int damage, string imageName, float colliderWidth, float colliderHeight, 
	float criticalHitChance, 
	bool destroyOnCollision, 
	float spawnXPosition, float spawnYPosition, float spawnRotation, float spriteScale, float xVelociy, float yVelocity, float lifespan) :
	DamagingRegion{ damage, imageName, colliderWidth, colliderHeight, criticalHitChance, destroyOnCollision, spawnXPosition, spawnYPosition, spriteScale },
	m_velocity{ Vector2(xVelociy, yVelocity) },
	m_lifespan{ lifespan }
{
	GameObject::getTransform()->setRotation(spawnRotation);
}

Projectile::~Projectile()
{}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void Projectile::onUpdate(int ticks)
{
	updatePosition(ticks);
	DamagingRegion::handleCollisions();
	updateLifespan(ticks);
}

/**
	Handles collisions for projectile damaging regions.
*/
void Projectile::handleSingleCollision(GameObject* other)
{
	auto otherId = other->getId();

	/* Ensure you don't collide with the thing that created you. */
	if (otherId != m_ownerId)
	{
		/* If the other thing is a character, damage it. */
		std::shared_ptr<CharacterController> ccOther = other->getComponent<CharacterController>();
		if (ccOther != nullptr)
		{
			m_hitList.insert(otherId);

			ccOther->takeDamage(m_damage, isCriticalHit());

			if (m_destroyOnCollision)
			{
				destroy(getId());
			}

			return;
		}

		/* In all other collisions, destroy if appropriate. */
		if (m_destroyOnCollision)
		{
			destroy(getId());
		}
	}
}

void Projectile::updatePosition(int ticks)
{
	float deltaTime = (float)ticks / 1000.0f;
	float xDelta = m_velocity.getX() * deltaTime;
	float yDelta = m_velocity.getY() * deltaTime;

	getTransform()->setPosition(
		getTransform()->getX() + xDelta,
		getTransform()->getY() + yDelta
	);
}

void Projectile::updateLifespan(int ticks)
{
	m_lifespan -= (float) ticks / 1000.0f;

	if (m_lifespan <= 0)
	{
		destroy(getId());
	}
}
