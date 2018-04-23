/*===================================================================================*//**
	BaseGreaves
	
	Abstract class for a base pair of greaves (leg armor).

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "Updateable.h"
#include "BaseEquippableItem.h"
class Vector2;

/*========================================================================================
	BaseGreaves	
========================================================================================*/
class BaseGreaves : public BaseEquippableItem, public Updateable, public std::enable_shared_from_this<BaseGreaves>

{
    /*----------------------------------------------------------------------------------------
		Static Fields
    ----------------------------------------------------------------------------------------*/
	public:
		static const std::string WOODEN_GREAVES_ICON_IMAGE_NAME;
		static const float WOODEN_GREAVES_COOLDOWN_TIME;
		static const float WOODEN_GREAVES_DASH_DURATION;
		static const float WOODEN_GREAVES_DASH_SPEED;

		static const std::string SILVER_GREAVES_ICON_IMAGE_NAME;
		static const float SILVER_GREAVES_COOLDOWN_TIME;
		static const float SILVER_GREAVES_DASH_DURATION;
		static const float SILVER_GREAVES_DASH_SPEED;

		static const std::string GOLD_GREAVES_ICON_IMAGE_NAME;
		static const float GOLD_GREAVES_COOLDOWN_TIME;
		static const float GOLD_GREAVES_DASH_DURATION;
		static const float GOLD_GREAVES_DASH_SPEED;

    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		float m_cooldownTime;
		float m_dashDuration;
		float m_dashSpeed;

		bool m_isActive;
		float m_timeUntilNextUse;
		float m_timeLeftInDash;
		std::unique_ptr<Vector2> m_dashDirection;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseGreaves() = delete;

		explicit BaseGreaves(std::string iconImageName, float cooldownTime, float dashDuration, float dashSpeed);

		virtual ~BaseGreaves() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual bool use();

		virtual void onStart();
		virtual void onUpdate(int ticks);
		virtual void onEnd();

		virtual void effect(int ticks);

		virtual void setProperties(std::string iconImageName, float cooldownTime, float dashDuration, float dashSpeed);

	protected:
		std::shared_ptr<BaseItem> addSubclassToInventory();

		virtual void updateEffect(int ticks);

		/*----------------------------------------------------------------------------------------
		| Setup Sprites and Animations
		----------------------------------------------------------------------------------------*/
		void setupSprites(std::string identifier);
};
