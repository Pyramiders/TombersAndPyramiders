/*===================================================================================*//**
	DamagingRegion
	
	Prefab class for a GameObject that causes damage to damageable objects when it 
	collides with them.
    
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "GameObject.h"
#include "SimpleSprite.h"
#include "Vector2.h"
#include <unordered_set>
class BaseWeapon;
class Collider;

/*========================================================================================
	DamagingRegion	
========================================================================================*/
class DamagingRegion : public SimpleSprite
{
    /*----------------------------------------------------------------------------------------
		Class Fields
    ----------------------------------------------------------------------------------------*/
	protected:
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    protected:
		std::shared_ptr<Collider> m_collider;
		int m_ownerId;
		int m_damage;
		float m_criticalHitChance;
		bool m_destroyOnCollision;
		std::unordered_set<int> m_hitList;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
		explicit DamagingRegion() = delete;

		explicit DamagingRegion(int damage, string imageName, float colliderWidth,
			float colliderHeight, float criticalHitChance, bool destroyOnCollision, float xPosition = 0, float yPosition = 0, float spriteScale = 1);

		virtual ~DamagingRegion() {};
		
    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		virtual void setOwnerId(int id);
		virtual void onUpdate(int ticks);
		virtual void clearHitList();

	protected:
		virtual void handleCollisions();
		virtual void handleSingleCollision(GameObject* other);
		virtual bool isCriticalHit();
};
