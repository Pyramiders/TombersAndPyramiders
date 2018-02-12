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

		explicit BaseProjectileWeapon(std::string projectileImageName, 
			Vector2 projectileColliderSize, Vector2 projectileSpawnOffsetFromHolder, 
			float projectileSpriteScale, Vector2 projectileVelocity, float projectileLifespan);

		virtual ~BaseProjectileWeapon() {};
};
