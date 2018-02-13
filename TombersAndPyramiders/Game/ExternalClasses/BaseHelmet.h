/*===================================================================================*//**
	BaseHelmet
	
	Abstract class for a base helmet.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

#pragma once

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseEquippableItem.h"

/*========================================================================================
	BaseHelmet	
========================================================================================*/
class BaseHelmet : public BaseEquippableItem, public std::enable_shared_from_this<BaseHelmet>
{
    /*----------------------------------------------------------------------------------------
		Instance Fields
    ----------------------------------------------------------------------------------------*/
    private:
		int m_durability; /* TODO: Decide if this is a number of headshots or an amount of damage to absorb. */
		float m_absorptionChance;

    /*----------------------------------------------------------------------------------------
		Resource Management
    ----------------------------------------------------------------------------------------*/
    public:
        /** Default constructor. */
        explicit BaseHelmet() = delete;

		explicit BaseHelmet(int durability, float absorptionChance);

		virtual ~BaseHelmet() {};

	/*----------------------------------------------------------------------------------------
		Instance Methods
	----------------------------------------------------------------------------------------*/
    public:
		virtual int absorbHeadshot(int damage);

	protected:
		std::shared_ptr<BaseItem> addSubclassToInventory();

    private:
		virtual void destroy();
};
