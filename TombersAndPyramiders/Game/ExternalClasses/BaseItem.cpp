/*===================================================================================*//**
	BaseItem
	
	Abstract class for an item that can be carried in an Inventory.

    @author Erick Fernandez de Arteaga
	
*//*====================================================================================*/

/*========================================================================================
	Dependencies
========================================================================================*/
#include "BaseItem.h"
#include "Inventory.h"

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
const float BaseItem::TICKS_PER_SECOND = 60;

/*----------------------------------------------------------------------------------------
	Instance Methods
----------------------------------------------------------------------------------------*/
void BaseItem::addToInventory(Inventory* inventory)
{
	m_inventory = inventory;

	if (m_inventory != nullptr)
	{
		addSubclassToInventory();
	}
}

GameObject* BaseItem::owner()
{
	return (m_inventory == nullptr) ? nullptr : m_inventory->getGameObject();
}
