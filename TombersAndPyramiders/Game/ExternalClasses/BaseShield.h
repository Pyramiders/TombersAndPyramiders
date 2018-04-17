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
		Static Fields
    ----------------------------------------------------------------------------------------*/
	public:
		static const string WOODEN_SHIELD_ICON_NAME;
		static const string WOODEN_SHIELD_IMAGE_NAME;
		static const float WOODEN_SHIELD_DAMAGE_MULT;
		static const float WOODEN_SHIELD_COOLDOWN_TIME;

		static const string SILVER_SHIELD_ICON_NAME;
		static const string SILVER_SHIELD_IMAGE_NAME;
		static const float SILVER_SHIELD_DAMAGE_MULT;
		static const float SILVER_SHIELD_COOLDOWN_TIME;

		static const string GOLD_SHIELD_ICON_NAME;
		static const string GOLD_SHIELD_IMAGE_NAME;
		static const float GOLD_SHIELD_DAMAGE_MULT;
		static const float GOLD_SHIELD_COOLDOWN_TIME;

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

		explicit BaseShield(string imageName, string iconName, float damageMultiplier, float cooldownTime);

		virtual ~BaseShield() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual bool use();

		virtual void onStart();
		virtual void onUpdate(int ticks);
		virtual void onEnd();

		virtual bool isBlocking();
		virtual int calculateRealDamage(int damage);

		virtual void setProperties(string imageName, string iconImageName, float damageMultiplier, float cooldownTime);

	protected:
		std::shared_ptr<BaseItem> addSubclassToInventory();
		virtual void updatePosition();
		virtual void updateBlock(int ticks);
};
