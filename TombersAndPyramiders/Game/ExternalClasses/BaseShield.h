/*===================================================================================*//**
	BaseShield
	
	Abstract class for a base shield.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Updateable.h"
#include "BaseEquippableItem.h"
#include "SimpleSprite.h"
#include "Vector2.h"

/*========================================================================================
	BaseShield	
========================================================================================*/
class BaseShield : public BaseEquippableItem, public Updateable, public std::enable_shared_from_this<BaseShield>
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	private:
		std::shared_ptr<SimpleSprite> m_sprite;
		Vector2 m_offsetFromHolder;
		float m_damageMultiplier;
		bool m_isBlocking;
		float m_blockCooldownTime;
		float m_timeUntilNextBlock;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
		explicit BaseShield() = delete;

		explicit BaseShield(string imageName, float damageMultiplier, float cooldownTime);

		virtual ~BaseShield() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual bool use();

		virtual void onStart();
		virtual void onUpdate(int ticks);
		virtual void onEnd();

		bool isBlocking();
		int calculateRealDamage(int damage);

	protected:
		std::shared_ptr<BaseItem> addSubclassToInventory();
		virtual void updatePosition();
		virtual void updateBlock(int ticks);
};
