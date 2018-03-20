/*===================================================================================*//**
	BaseLongbow

	Abstract class for a base longbow.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseLongbow.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const float BaseLongbow::LONGBOW_PROJECTILE_COLLIDER_WIDTH = 0.5;
const float BaseLongbow::LONGBOW_PROJECTILE_COLLIDER_HEIGHT = 0.5;
const float BaseLongbow::LONGBOW_PROJECTILE_SPRITE_SCALE = 1.0;
const float BaseLongbow::LONGBOW_PROJECTILE_SPAWN_X_OFFSET_FROM_HOLDER = 1;
const float BaseLongbow::LONGBOW_PROJECTILE_SPAWN_Y_OFFSET_FROM_HOLDER = 0;
const float BaseLongbow::LONGBOW_PROJECTILE_LIFESPAN = 3;
const float BaseLongbow::LONGBOW_PROJECTILE_X_VELOCITY = 40;
const float BaseLongbow::LONGBOW_PROJECTILE_Y_VELOCITY = 0;
const float BaseLongbow::LONGBOW_CRITICAL_HIT_CHANCE = 0.05f;
const float BaseLongbow::LONGBOW_ATTACK_COOLDOWN_TIME = 0.5f;

/*----------------------------------------------------------------------------------------
	Resource Methods
----------------------------------------------------------------------------------------*/
BaseLongbow::BaseLongbow(int damage, std::string projectileImageName,
	Vector2 projectileColliderSize, bool destroyProjectilesOnCollision,
	Vector2 projectileSpawnOffsetFromHolder,
	float projectileSpriteScale, Vector2 projectileVelocity, float projectileLifespan) :
	BaseProjectileWeapon{ damage, projectileImageName, projectileColliderSize, 
	destroyProjectilesOnCollision, LONGBOW_CRITICAL_HIT_CHANCE, LONGBOW_ATTACK_COOLDOWN_TIME, 
	projectileSpawnOffsetFromHolder, projectileSpriteScale, projectileVelocity, projectileLifespan }
{}
