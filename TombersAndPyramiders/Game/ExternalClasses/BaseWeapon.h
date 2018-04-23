/*===================================================================================*//**
	BaseWeapon
	
	Abstract class for a base weapon.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Updateable.h"
#include "BaseEquippableItem.h"
#include <string>
#include "ComplexSprite.h"

/*========================================================================================
	BaseWeapon	
========================================================================================*/
class BaseWeapon : public BaseEquippableItem, public Updateable, public std::enable_shared_from_this<BaseWeapon>
{
    /*----------------------------------------------------------------------------------------
		Class Fields
    ----------------------------------------------------------------------------------------*/
	public:
		static const float CRITICAL_HIT_DAMAGE_MULTIPLIER;

    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		int m_damage;
		float m_criticalHitChance;
		float m_attackCooldownTime;
		bool m_isAttacking;
		float m_timeUntilNextAttack;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseWeapon() = delete;

		explicit BaseWeapon(int damage, float criticalHitChance, float attackCooldownTime);

		virtual ~BaseWeapon() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual void setOwnerId(int id) = 0;

		/**
			Uses the weapon.
			This should be called every update that the controller gets input to use the weapon.

			Returns true if the weapon began attacking as a result of the call and false otherwise.

			Weapon classes that implement this will treat this either as a "trigger", 
			starting the use of the weapon and ignoring subsequent calls until the weapon 
			is ready for use again (e.g., swinging a sword), OR as a continuous "hold" for 
			weapons that can be used continuously (e.g., a flail that is swung around for 
			as long as the player holds the key).
		*/
		virtual bool use() = 0;

		/**
			Called by the use() method on the update that the weapon begins attacking.
		*/
		virtual void onStart() = 0;
		
		/**
			Called every update regardless of onStart() and onEnd() calls.
		*/
		virtual void onUpdate(int ticks) = 0;
		
		/**
			Called by the weapon on the update that the weapon stops attacking.
		*/
		virtual void onEnd() = 0;

		bool isAttacking();

	protected:
		std::shared_ptr<BaseItem> addSubclassToInventory();
};
