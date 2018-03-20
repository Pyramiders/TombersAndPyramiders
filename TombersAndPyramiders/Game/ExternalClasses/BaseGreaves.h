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

/*========================================================================================
	BaseGreaves	
========================================================================================*/
class BaseGreaves : public BaseEquippableItem, public Updateable, public std::enable_shared_from_this<BaseGreaves>

{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
	protected:
		float m_cooldownTime;
		bool m_isActive;
		float m_timeUntilNextUse;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseGreaves() = delete;

		explicit BaseGreaves(float cooldownTime);

		virtual ~BaseGreaves() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual bool use();

		virtual void onStart();
		virtual void onUpdate(int ticks);
		virtual void onEnd();

		virtual void effect(int ticks) = 0;

	protected:
		std::shared_ptr<BaseItem> addSubclassToInventory();

		virtual void updateEffect(int ticks);
};
