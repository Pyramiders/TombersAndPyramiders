/*===================================================================================*//**
	BaseProjectileWeapon
	
	Abstract class for a base projectile weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseWeapon.h"
#include "Vector2.h"
#include <string>

/*========================================================================================
	BaseProjectileWeapon	
========================================================================================*/
class BaseProjectileWeapon : public BaseWeapon
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		std::string m_projectileImageName;
		Vector2 m_projectileColliderSize;
		bool m_destroyProjectilesOnCollision;
		Vector2 m_projectileSpawnOffsetFromHolder;
		float m_projectileSpriteScale;
		Vector2 m_projectileVelocity;
		float m_projectileLifespan;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseProjectileWeapon() = delete;

		explicit BaseProjectileWeapon(int damage, std::string projectileImageName, 
			Vector2 projectileColliderSize, bool destroyprojectilesOnCollision, float criticalHitChance, 
			float attackCooldownTime, 
			Vector2 projectileSpawnOffsetFromHolder, float projectileSpriteScale, 
			Vector2 projectileVelocity, float projectileLifespan);

		virtual ~BaseProjectileWeapon() {};
		
    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		virtual void setOwnerId(int id);
		virtual bool use();

		virtual void onStart();
		virtual void onUpdate(int ticks);
		virtual void onEnd();

	protected:
		virtual void updateAttack(int ticks);
		
		/**
			Returns a Vector2 containing the coordinates where projectiles should be spawned 
			this tick.
		*/
		virtual Vector2 getProjectileSpawnPoint();
		
		/**
			Returns a Vector2 containing the velocity projectiles should be spawned with
			this tick.
		*/
		virtual Vector2 getProjectileVelocity();
};
