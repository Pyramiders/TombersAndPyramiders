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

const int BaseLongbow::WOODEN_LONGBOW_DAMAGE = 20;
const std::string BaseLongbow::WOODEN_LONGBOW_IMAGE_NAME = "WoodenLongbow.png";
const std::string BaseLongbow::WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME = "TempWoodenArrow.png";
const bool BaseLongbow::WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION = true;

const int BaseLongbow::SILVER_LONGBOW_DAMAGE = 35;
const std::string BaseLongbow::SILVER_LONGBOW_IMAGE_NAME = "SilverLongbow.png";
const std::string BaseLongbow::SILVER_LONGBOW_PROJECTILE_IMAGE_NAME = "TempSilverArrow.png";
const bool BaseLongbow::SILVER_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION = true;

const int BaseLongbow::GOLD_LONGBOW_DAMAGE = 50;
const std::string BaseLongbow::GOLD_LONGBOW_IMAGE_NAME = "GoldLongbow.png";
const std::string BaseLongbow::GOLD_LONGBOW_PROJECTILE_IMAGE_NAME = "TempGoldArrow.png";
const bool BaseLongbow::GOLD_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION = false;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseLongbow::BaseLongbow(int damage, std::string bowImageName, std::string projectileImageName, bool destroyProjectilesOnCollision) :
	BaseProjectileWeapon{ damage, projectileImageName, 
	Vector2(LONGBOW_PROJECTILE_COLLIDER_WIDTH, LONGBOW_PROJECTILE_COLLIDER_HEIGHT), 
	destroyProjectilesOnCollision, LONGBOW_CRITICAL_HIT_CHANCE, LONGBOW_ATTACK_COOLDOWN_TIME, 
	Vector2(LONGBOW_PROJECTILE_SPAWN_X_OFFSET_FROM_HOLDER, LONGBOW_PROJECTILE_SPAWN_Y_OFFSET_FROM_HOLDER), 
	LONGBOW_PROJECTILE_SPRITE_SCALE, Vector2(LONGBOW_PROJECTILE_X_VELOCITY, LONGBOW_PROJECTILE_Y_VELOCITY), 
	LONGBOW_PROJECTILE_LIFESPAN }
{
	m_itemIcon = bowImageName;
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseLongbow::setProperties(int damage, std::string bowImageName, std::string projectileImageName, bool destroyProjectilesOnCollision)
{
	m_damage = damage;
	m_itemIcon = bowImageName;
	m_projectileImageName = projectileImageName;
	m_destroyProjectilesOnCollision = destroyProjectilesOnCollision;
}
