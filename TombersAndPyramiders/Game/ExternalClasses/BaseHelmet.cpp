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
BaseHelmet::BaseHelmet(float criticalResistChance) :
	m_criticalResistChance{ criticalResistChance }
{
	if (m_criticalResistChance < 0)
	{
		throw std::invalid_argument("BaseHelmet::BaseHelmet(): m_criticalResistChance must be non-negative.");
	}
}

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
bool BaseHelmet::doesAvoidCriticalHit()
{
	return (s_random.random0to1() < m_criticalResistChance);
}

std::shared_ptr<BaseItem> BaseHelmet::addSubclassToInventory()
{
	return m_inventory->setHelmet(shared_from_this());
}
