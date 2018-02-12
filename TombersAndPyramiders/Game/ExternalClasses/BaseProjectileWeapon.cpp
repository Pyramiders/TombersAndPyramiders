/*===================================================================================*//**
	BaseProjectileWeapon

	Abstract class for a base projectile weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseProjectileWeapon.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseProjectileWeapon::BaseProjectileWeapon(std::string projectileImageName,
	Vector2 projectileColliderSize, Vector2 projectileSpawnOffsetFromHolder,
	float projectileSpriteScale, Vector2 projectileVelocity, float projectileLifespan) :
	m_projectileImageName{ projectileImageName }, 
	m_projectileColliderSize{ projectileColliderSize }, 
	m_projectileSpawnOffsetFromHolder{ projectileSpawnOffsetFromHolder }, 
	m_projectileSpriteScale{ projectileSpriteScale }, 
	m_projectileVelocity{ projectileVelocity }, 
	m_projectileLifespan{ projectileLifespan }
{}
