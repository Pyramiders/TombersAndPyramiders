/*===================================================================================*//**
	Projectile
	
	A Damaging region that is fired by a projectile weapon, moves, and destroys itself 
	after a set duration or after hitting something.
    
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Projectile.h"
#include "BaseItem.h"
#include <memory>

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
Projectile::Projectile(BaseWeapon* weapon, string imageName, float colliderWidth, float colliderHeight, 
	float spawnXPosition, float spawnYPosition, float spriteScale, float xVelociy, float yVelocity, float lifespan) :
	DamagingRegion{ weapon, imageName, colliderWidth, colliderHeight, spawnXPosition, spawnYPosition, spriteScale }, 
	m_velocity{ Vector2(xVelociy, yVelocity) },
	m_lifespan{ lifespan }
{}

Projectile::~Projectile()
{}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void Projectile::onUpdate(int ticks)
{
	updatePosition(ticks);
	updateLifespan(ticks);
}

void Projectile::updatePosition(int ticks)
{
	float deltaTime = ticks / BaseItem::TICKS_PER_SECOND;
	float xDelta = m_velocity.getX() * deltaTime;
	float yDelta = m_velocity.getY() * deltaTime;

	getTransform()->setPosition(
		getTransform()->getX() + xDelta,
		getTransform()->getY() + yDelta
	);
}

void Projectile::updateLifespan(int ticks)
{
	m_lifespan -= ticks / BaseItem::TICKS_PER_SECOND;

	if (m_lifespan <= 0)
	{
		
		destroy(getId());
	}
}
