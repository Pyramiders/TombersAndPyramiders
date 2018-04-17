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
	public:
		static const int WOODEN_SHORTSWORD_DAMAGE;
		static const string WOODEN_SHORTSWORD_IMAGE_NAME;
		static const bool WOODEN_SHORTSWORD_DESTROY_ON_COLLISION;

		static const int SILVER_SHORTSWORD_DAMAGE;
		static const string SILVER_SHORTSWORD_IMAGE_NAME;
		static const bool SILVER_SHORTSWORD_DESTROY_ON_COLLISION;

		static const int GOLD_SHORTSWORD_DAMAGE;
		static const string GOLD_SHORTSWORD_IMAGE_NAME;
		static const bool GOLD_SHORTSWORD_DESTROY_ON_COLLISION;

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

    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
    public:
		void setProperties(int damage, string imageName, bool destroyOnCollision);
};
