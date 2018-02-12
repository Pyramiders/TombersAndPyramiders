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
const std::string WoodenLongbow::WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME = "IceTile.png";

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
WoodenLongbow::WoodenLongbow() :
	BaseLongbow{ WOODEN_LONGBOW_PROJECTILE_IMAGE_NAME,
		Vector2(LONGBOW_PROJECTILE_COLLIDER_WIDTH, LONGBOW_PROJECTILE_COLLIDER_HEIGHT), 
		Vector2(LONGBOW_PROJECTILE_SPAWN_X_OFFSET_FROM_HOLDER, LONGBOW_PROJECTILE_SPAWN_Y_OFFSET_FROM_HOLDER), 
		LONGBOW_PROJECTILE_SPRITE_SCALE, 
		Vector2(LONGBOW_PROJECTILE_X_VELOCITY, LONGBOW_PROJECTILE_Y_VELOCITY), 
		LONGBOW_PROJECTILE_LIFESPAN }
{}
