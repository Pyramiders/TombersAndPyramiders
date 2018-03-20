/*===================================================================================*//**
	BaseShortsword
	
	Abstract class for a base shortsword.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseMeleeWeapon.h"

/*========================================================================================
	BaseWeapon	
========================================================================================*/
class BaseShortsword : public BaseMeleeWeapon
{
    /*----------------------------------------------------------------------------------------
		Static Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		static const float SHORTSWORD_COLLIDER_WIDTH;
		static const float SHORTSWORD_COLLIDER_HEIGHT;
		static const float SHORTSWORD_COLLIDER_SCALE;
		static const float SHORTSWORD_X_OFFSET_FROM_HOLDER;
		static const float SHORTSWORD_Y_OFFSET_FROM_HOLDER;
		static const float SHORTSWORD_CRITICAL_HIT_CHANCE;
		static const float SHORTSWORD_ATTACK_COOLDOWN_TIME;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseShortsword() = delete;

		explicit BaseShortsword(int damage, string imageName, bool destroyOnCollision);

		virtual ~BaseShortsword() {};
};
