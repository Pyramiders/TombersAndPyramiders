/*===================================================================================*//**
	BaseHelmet
	
	Abstract class for a base helmet.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include <stdexcept>
#include "BaseHelmet.h"
#include "Inventory.h"

/*----------------------------------------------------------------------------------------
	Resource Management
----------------------------------------------------------------------------------------*/
BaseHelmet::BaseHelmet(int durability, float absorptionChance) :
	m_durability{ durability }, m_absorptionChance{ absorptionChance }
{
	if (durability < 0)
	{
		throw std::invalid_argument("BaseHelmet::BaseHelmet: durability must 0 or greater.");
	}

	if (absorptionChance < 0 ||
		absorptionChance > 1)
	{
		throw std::invalid_argument("BaseHelmet::BaseHelmet: absorptionChance must be in the range [0-1].");
	}
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
int BaseHelmet::absorbHeadshot(int damage)
{
	return damage;
}

std::shared_ptr<BaseItem> BaseHelmet::addSubclassToInventory()
{
	return m_inventory->setHelmet(shared_from_this());
}

void BaseHelmet::destroy()
{
	/* Nothing to do for now. */
}
