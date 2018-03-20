/*===================================================================================*//**
	BaseLongbow

	Abstract class for a base longbow.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "WoodenLongbow.h"

/*----------------------------------------------------------------------------------------
	Static Fields
----------------------------------------------------------------------------------------*/
const int WoodenLongbow::WOODEN_LONGBOW_DAMAGE = 20;
const std::string WoodenLongbow::WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME = "TempWoodenArrow.png";
const bool WoodenLongbow::WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION = true;

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
WoodenLongbow::WoodenLongbow() :
	BaseLongbow{ WOODEN_LONGBOW_DAMAGE, WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME,
		Vector2(LONGBOW_PROJECTILE_COLLIDER_WIDTH, LONGBOW_PROJECTILE_COLLIDER_HEIGHT), 
		WOODEN_LONGBOW_DESTROY_PROJECTILES_ON_COLLISION,
		Vector2(LONGBOW_PROJECTILE_SPAWN_X_OFFSET_FROM_HOLDER, LONGBOW_PROJECTILE_SPAWN_Y_OFFSET_FROM_HOLDER), 
		LONGBOW_PROJECTILE_SPRITE_SCALE, 
		Vector2(LONGBOW_PROJECTILE_X_VELOCITY, LONGBOW_PROJECTILE_Y_VELOCITY), 
		LONGBOW_PROJECTILE_LIFESPAN }
{
	m_itemIcon = "WoodenLongbow.png"; 
}
