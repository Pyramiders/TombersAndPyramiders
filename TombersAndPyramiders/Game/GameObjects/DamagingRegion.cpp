/*===================================================================================*//**
	DamagingRegion
	
	Prefab class for a GameObject that causes damage to damageable objects when it 
	collides with them.
    
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <stdexcept>
#include "DamagingRegion.h"
#include "BoxCollider.h"
#include "CharacterController.h"
#include "Damageable.h"
#include "RandomHelper.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
RandomHelper DamagingRegion::s_random = RandomHelper();

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
DamagingRegion::DamagingRegion(int damage, string imageName, float colliderWidth, 
	float colliderHeight, float criticalHitChance, bool destroyOnCollision, float xPosition, float yPosition, float spriteScale) :
	SimpleSprite{ imageName, xPosition, yPosition, 0, spriteScale },
	m_damage{ damage }, 
	m_criticalHitChance{ criticalHitChance },
	m_destroyOnCollision{ destroyOnCollision },
	m_hitList { std::unordered_set<int>() }
{
	if (colliderWidth < 0)
	{
		throw std::invalid_argument("DamagingRegion::DamagingRegion(): colliderWidth must be non-negative.");
	}

	if (colliderHeight < 0)
	{
		throw std::invalid_argument("DamagingRegion::DamagingRegion(): colliderHeight must be non-negative.");
	}

 	m_collider = addComponent<BoxCollider>(this, colliderWidth, colliderHeight);
	m_collider->setIsTrigger(true);
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void DamagingRegion::setOwnerId(int id)
{
	m_ownerId = id;
}

void DamagingRegion::onUpdate(int ticks)
{
	handleCollisions();
}

void DamagingRegion::clearHitList()
{
	m_hitList.clear();
}

void DamagingRegion::handleCollisions()
{
	if (m_collider != nullptr && m_collider->collisionDetected())
	{
		for (int i = 0; i < m_collider->getColliders().size(); i++)
		{
			handleSingleCollision(m_collider->getColliders()[i]);
		}
	}
}

/**
	Handles collisions for melee weapon damaging regions.
*/
void DamagingRegion::handleSingleCollision(GameObject* other)
{
	auto otherId = other->getId();

	/* Ensure you don't collide with your owner or collide with a given object more than once. */
	if ( otherId != m_ownerId &&
		 m_hitList.count(otherId) == 0 )
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
	}
}

bool DamagingRegion::isCriticalHit()
{
	return (s_random.random0to1() < m_criticalHitChance);
}
