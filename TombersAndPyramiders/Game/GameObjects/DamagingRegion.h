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
class BaseWeapon;

/*========================================================================================
	DamagingRegion	
========================================================================================*/
class DamagingRegion : public SimpleSprite
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    private:
		BaseWeapon* _weapon;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
		explicit DamagingRegion() = delete;

		explicit DamagingRegion(BaseWeapon* weapon, string imageName, float colliderWidth,
			float colliderHeight, float xPosition = 0, float yPosition = 0, float spriteScale = 1);

		virtual ~DamagingRegion() {};
};
