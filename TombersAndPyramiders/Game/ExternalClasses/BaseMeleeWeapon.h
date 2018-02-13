/*===================================================================================*//**
	BaseMeleeWeapon
	
	Abstract class for a base melee weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseWeapon.h"
#include "DamagingRegion.h"
#include "Vector2.h"

/*========================================================================================
	BaseMeleeWeapon	
========================================================================================*/
class BaseMeleeWeapon : public BaseWeapon
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		DamagingRegion m_damagingRegion;
		Vector2 m_offsetFromHolder;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseMeleeWeapon(string imageName, float colliderWidth, float colliderHeight, 
			float xOffsetFromHolder, float yOffsetFromHolder, float colliderScale = 1);

		virtual ~BaseMeleeWeapon() {};

	
    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		void updatePosition();
};
