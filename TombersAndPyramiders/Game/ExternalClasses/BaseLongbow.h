/*===================================================================================*//**
	BaseLongbow
	
	Abstract class for a base longbow.
    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseProjectileWeapon.h"
#include <string>

/*========================================================================================
	BaseLongbow	
========================================================================================*/
class BaseLongbow : public BaseProjectileWeapon
{
    /*----------------------------------------------------------------------------------------
		Static Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		static const float LONGBOW_PROJECTILE_COLLIDER_WIDTH;
		static const float LONGBOW_PROJECTILE_COLLIDER_HEIGHT;
		static const float LONGBOW_PROJECTILE_SPRITE_SCALE;
		static const float LONGBOW_PROJECTILE_SPAWN_X_OFFSET_FROM_HOLDER;
		static const float LONGBOW_PROJECTILE_SPAWN_Y_OFFSET_FROM_HOLDER;
		static const float LONGBOW_PROJECTILE_LIFESPAN;
		static const float LONGBOW_PROJECTILE_X_VELOCITY;
		static const float LONGBOW_PROJECTILE_Y_VELOCITY;
		static const float LONGBOW_CRITICAL_HIT_CHANCE;
		static const float LONGBOW_ATTACK_COOLDOWN_TIME;
		
	public:
		static const int WOODEN_LONGBOW_DAMAGE;
		static const std::string WOODEN_LONGBOW_IMAGE_NAME;
		static const std::string WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME;
		static const bool WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION;

		static const int SILVER_LONGBOW_DAMAGE;
		static const std::string SILVER_LONGBOW_IMAGE_NAME;
		static const std::string SILVER_LONGBOW_PROJECTILE_IMAGE_NAME;
		static const bool SILVER_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION;

		static const int GOLD_LONGBOW_DAMAGE;
		static const std::string GOLD_LONGBOW_IMAGE_NAME;
		static const std::string GOLD_LONGBOW_PROJECTILE_IMAGE_NAME;
		static const bool GOLD_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseLongbow() = delete;

		explicit BaseLongbow(int damage, std::string bowImageName, std::string projectileImageName, bool destroyProjectilesOnCollision);

		virtual ~BaseLongbow() {};

	
    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
    public:
		void setProperties(int damage, std::string bowImageName, 
			std::string projectileImageName, bool destroyProjectilesOnCollision);
};
