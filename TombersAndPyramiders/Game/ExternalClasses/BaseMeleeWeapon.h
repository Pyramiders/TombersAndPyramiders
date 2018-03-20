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
#include <memory>

/*========================================================================================
	BaseMeleeWeapon	
========================================================================================*/
class BaseMeleeWeapon : public BaseWeapon
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		std::shared_ptr<DamagingRegion> m_damagingRegion;
		Vector2 m_offsetFromHolder;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
		explicit BaseMeleeWeapon() = delete;

		explicit BaseMeleeWeapon(int damage, string imageName, float colliderWidth, float colliderHeight, 
			bool destroyOnCollision, float criticalHitChance, float attackCooldownTime, 
			float xOffsetFromHolder, float yOffsetFromHolder, float colliderScale = 1);

		virtual ~BaseMeleeWeapon() {};

	
    /*----------------------------------------------------------------------------------------
		Instance Methods
    ----------------------------------------------------------------------------------------*/
	public:
		virtual void setOwnerId(int id);
		virtual bool use();

		virtual void onStart();
		virtual void onUpdate(int ticks);
		virtual void onEnd();

		virtual void updatePosition();

	private:
		void updateAttack(int ticks);
};
